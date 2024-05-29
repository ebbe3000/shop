#include "database.h"


Database::Database() : db(QSqlDatabase::addDatabase("QMYSQL")) {
    db.setHostName("localhost");
    db.setDatabaseName("shop_db");
    db.setUserName("root");
    db.setPassword("");
    db.setPort(3306);
    db.open();
}


Database::~Database() {
    db.close();
}


bool Database::isConnected() {
    return db.isOpen();
}


void Database::closeDb() {
    db.close();
}


bool Database::isEmailInDb(const User& user) {
    QSqlQuery query("SELECT email FROM users "
                    "WHERE email = '" + user.getEmail() + "';");

    if (query.next())
        return true;

    return false;
}


void Database::addUserToDatabase(const User& user) {
    QSqlQuery query("CALL insertUser('" + user.getName() + "', "
                                    "'" + user.getSurname() + "', "
                                    "'" + user.getEmail() + "', "
                                    "'" + user.getPasswd() + "', "
                                    "'" + user.getProvince() + "', "
                                    "'" + user.getP_code() + "', "
                                    "'" + user.getCity() + "', "
                                    "'" + user.getAddress() + "');");
}


bool Database::isUserInDb(const QString& email, const QString& passwd, User*& user) {
    QSqlQuery query("SELECT u.id_u, u.name, u.surname, u.email, u.passwd, p.name, u.p_code, u.city, u.address "
                    "FROM users u INNER JOIN provinces p ON u.id_p = p.id_p "
                    "WHERE u.email = '" + email + "' AND u.passwd = '" + passwd + "';");

    if (!query.next())
        return false;

    user = new User(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(),
                    query.value(4).toString(), query.value(5).toString(), query.value(6).toString(), query.value(7).toString(),
                    query.value(8).toString());

    return true;
}


QVector<Product*> Database::getUsersSellProducts(const int id) {
    QSqlQuery query("SELECT id_p, id_u, name, price, amount, add_date, description "
                    "FROM products "
                    "WHERE id_u = " + QString::number(id) + ";");

    QVector<Product*> res;

    while (query.next()) {
        QVector<QString> tmp;
        QSqlQuery p_query("SELECT path "
                          "FROM path_to_images "
                          "WHERE id_p = " + query.value(0).toString() + ";");

        while (p_query.next())
            tmp.push_back(p_query.value(0).toString());

        Product* prod = new Product(query.value(0).toInt(), query.value(1).toInt(),
                                    query.value(2).toString(), query.value(3).toDouble(),
                                    query.value(4).toInt(), query.value(5).toString(),
                                    query.value(6).toString(), std::move(tmp));

        res.push_back(prod);
    }

    return res;
}


int Database::addProductToDatabase(const Product& product) {
    QSqlQuery query("INSERT INTO products(id_u, name, price, amount, add_date, description) "
                    "VALUES (" + QString::number(product.getIdU()) +
                    ", '" + product.getName() +
                    "', " + QString::number(product.getPrice()) +
                    ", " + QString::number(product.getAmount()) +
                    ", CURDATE(), '" + product.getDescribtion() + "');");
    return query.lastInsertId().toInt();
}


void Database::addPathToProductToDatabase(const int id_p, const QString& path) {
    QSqlQuery query("INSERT INTO path_to_images "
                    "VALUES (" + QString::number(id_p) + ", '" + path + "');");
}


void Database::addCategorizedProduct(const int id_p, const int id_c) {
    QSqlQuery query("INSERT INTO categorized_products "
                    "VALUES (" + QString::number(id_p) + ", " + QString::number(id_c) + ");");
}


QVector<Product*> Database::getClientsProducts(const int id_u) {
    QSqlQuery query("SELECT id_p, id_u, name, price, amount, add_date, description "
                    "FROM products "
                    "WHERE id_u = " + QString::number(id_u) + ";");

    QVector<Product*> result;

    while (query.next()) {

        QSqlQuery img_paths("SELECT path "
                            "FROM path_to_images "
                            "WHERE id_p = " + QString::number(query.value(0).toInt()) + ";");

        QVector<QString> paths;
        while (img_paths.next())
            paths.push_back(img_paths.value(0).toString());

        result.push_back(new Product(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toString(),
                                     query.value(3).toDouble(), query.value(4).toInt(), query.value(5).toString(),
                                     query.value(6).toString(), std::move(paths)));
    }

    return result;
}


QString Database::getUserNameAndSurname(const int id_u) {
    QSqlQuery query("SELECT name, surname "
                    "FROM users "
                    "WHERE id_u = " + QString::number(id_u) + ";");

    query.next();

    return query.value(0).toString() + " " + query.value(1).toString();
}


void Database::deleteProduct(const int id_p) {
    QSqlQuery query("DELETE FROM products "
                    "WHERE id_p = " + QString::number(id_p) + ";");
}


QVector<Product*> Database::getAllProducts(const int page_index, const int page_limit, int& number_of_records) {
    QSqlQuery records_amount("SELECT COUNT(id_p) "
                             "FROM products;");
    records_amount.next();
    number_of_records = records_amount.value(0).toInt();

    QSqlQuery query("SELECT id_p, id_u, name, price, amount, add_date, description "
                    "FROM products "
                    "ORDER BY id_p "
                    "LIMIT " + QString::number(page_limit) + " OFFSET " + QString::number(page_limit * page_index) + ";");

    QVector<Product*> result;

    while (query.next()) {
        QSqlQuery img_paths("SELECT path "
                            "FROM path_to_images "
                            "WHERE id_p = " + QString::number(query.value(0).toInt()) + ";");

        QVector<QString> paths;
        while (img_paths.next())
            paths.push_back(img_paths.value(0).toString());

        result.push_back(new Product(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toString(),
                                     query.value(3).toDouble(), query.value(4).toInt(), query.value(5).toString(),
                                     query.value(6).toString(), std::move(paths)));
    }

    return result;
}


QVector<Product*> Database::getProductsByCategories(const int page_index, const int page_limit, int& number_of_records,
                                                    const QVector<int>& categories) {
    QString command = "SELECT id_p "
                      "FROM categorized_products "
                      "WHERE ";

    for (QVector<int>::const_iterator it = categories.begin(); it != categories.end(); ++it)
        if (it == categories.begin())
            command += "id_c = " + QString::number(*it);
        else
            command += " OR id_c = " + QString::number(*it);

    command += " GROUP BY id_p "
               "HAVING COUNT(id_p) >= " + QString::number(categories.size()) + " "
               "ORDER BY id_p;";

    QSqlQuery query(command);

    number_of_records = query.size();

    command.chop(1);

    query.prepare("SELECT id_p, id_u, name, price, amount, add_date, description "
                  "FROM products "
                  "WHERE id_p IN (" + command + ") "
                  "LIMIT " + QString::number(page_limit) + " OFFSET " + QString::number(page_limit * page_index) + ";");

    query.exec();

    QVector<Product*> result;

    while (query.next()) {
        QSqlQuery img_paths("SELECT path "
                            "FROM path_to_images "
                            "WHERE id_p = " + QString::number(query.value(0).toInt()) + ";");

        QVector<QString> paths;
        while (img_paths.next())
            paths.push_back(img_paths.value(0).toString());

        result.push_back(new Product(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toString(),
                                     query.value(3).toDouble(), query.value(4).toInt(), query.value(5).toString(),
                                     query.value(6).toString(), std::move(paths)));
    }

    return result;
}


void Database::reduceProductAmount(const int id_p, const int amount) {
    QSqlQuery update("UPDATE products "
                     "SET amount = amount - " + QString::number(amount) + " "
                    "WHERE id_p = " + QString::number(id_p) + ";");

    QSqlQuery delete_from_shopping_carts("DELETE FROM shopping_carts "
                                         "WHERE id_p = " + QString::number(id_p) + ";");
}


void Database::moveAmountFromProducts(const int id_p, const int amount) {
    QSqlQuery update("UPDATE products "
                     "SET amount = amount - " + QString::number(amount) + " "
                     "WHERE id_p = " + QString::number(id_p) + ";");
}


Product* Database::getProductById(const int id_p) {
    QSqlQuery query("SELECT id_p, id_u, name, price, amount, add_date, description "
                    "FROM products "
                    "WHERE id_p = " + QString::number(id_p) + ";");

    query.next();

    QSqlQuery img_paths("SELECT path "
                        "FROM path_to_images "
                        "WHERE id_p = " + QString::number(query.value(0).toInt()) + ";");

    QVector<QString> paths;
    while (img_paths.next())
        paths.push_back(img_paths.value(0).toString());

    return new Product(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toString(),
                       query.value(3).toDouble(), query.value(4).toInt(), query.value(5).toString(),
                       query.value(6).toString(), std::move(paths));
}


void Database::addToShoppingCart(const int user_id, const int id_p, const int amount) {
    QSqlQuery query("INSERT INTO shopping_carts "
                    "VALUES (" + QString::number(user_id) + ", " + QString::number(id_p) + ", " + QString::number(amount) + ");");
}


QVector<Product*> Database::getProductFromShoppingCart(const int id_u) {
    QSqlQuery products_and_amount("SELECT id_p, amount "
                                  "FROM shopping_carts "
                                  "WHERE id_u = " + QString::number(id_u) + ";");

    QVector<Product*> result;
    while (products_and_amount.next()) {
        Product* prod = getProductById(products_and_amount.value(0).toInt());
        prod->setAmount(products_and_amount.value(1).toInt());
        result.push_back(prod);
    }

    return result;
}


void Database::updateShoppingCartAmount(const int id_p, const int newAmount) {
    QSqlQuery update("UPDATE shopping_carts "
                     "SET amount = " + QString::number(newAmount) + " "
                     "WHERE id_p = " + QString::number(id_p) + ";");
}


void Database::deleteFromShoppingCart(const int id_u, const int id_p) {
    QSqlQuery delet("DELETE FROM shopping_carts "
                     "WHERE id_u = " + QString::number(id_u) + " AND id_p = " + QString::number(id_p) + ";");
}


void Database::reduceProductAmountInShoppingCart(const int id_u, const int id_p, const int amount) {
    // QSqlQuery max_amount("SELECT amount "
    //                      "FROM shopping_carts "
    //                      "WHERE id_u = " + QString::number(id_u) + " AND id_p = " + QString::number(id_p) + ";");
    // max_amount.next();
    // int tmp = max_amount.value(0).toInt();

    QSqlQuery update("UPDATE shopping_carts "
                     "SET amount = amount - " + QString::number(amount) + " "
                     "WHERE id_u = " + QString::number(id_u) + " AND id_p = " + QString::number(id_p) + ";");
}


void Database::returnProductsToShop(const int id_p, const int amount) {
    QSqlQuery update("UPDATE products "
                     "SET amount = amount + " + QString::number(amount) + " "
                     "WHERE id_p = " + QString::number(id_p) + ";");
}
