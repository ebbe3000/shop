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
    QSqlQuery new_item("SELECT id_p "
                       "FROM products "
                       "WHERE id_u = " + QString::number(product.getIdU()) +
                       " AND name = '" + product.getName() +
                       "' AND price = " + QString::number(product.getPrice()) +
                       " AND amount = " + QString::number(product.getAmount()) +
                       " AND description = '" + product.getDescribtion() + "';");
    int id_p;
    while (new_item.next())
        id_p = new_item.value(0).toInt();
    return id_p;
}


void Database::addPathToProductToDatabase(const int id_p, const QString& path) {
    QSqlQuery query("INSERT INTO path_to_images "
                    "VALUES (" + QString::number(id_p) + ", '" + path + "');");
}


void Database::addCategorizedProduct(const int id_p, const int id_c) {
    QSqlQuery query("INSERT INTO categorized_products VALUES (" + QString::number(id_p) + ", " + QString::number(id_c) + ");");
}
