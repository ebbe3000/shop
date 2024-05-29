#ifndef DATABASE_H
#define DATABASE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>

#include "user.h"
#include "product.h"

class Database
{
    QSqlDatabase db;

public:
    Database();
    ~Database();

    bool isConnected();
    void closeDb();
    bool isEmailInDb(const User& user);
    void addUserToDatabase(const User& user);
    bool isUserInDb(const QString& email, const QString& passwd, User*& user);

    QVector<Product*> getUsersSellProducts(const int id);

    int addProductToDatabase(const Product& product);

    void addPathToProductToDatabase(const int id_p, const QString& path);

    void addCategorizedProduct(const int id_p, const int id_c);

    QVector<Product*> getClientsProducts(const int id_u);

    QString getUserNameAndSurname(const int id_u);

    void deleteProduct(const int id_p);

    QVector<Product*> getAllProducts(const int page_index, const int page_limit,
                                     int& number_of_records);

    QVector<Product*> getProductsByCategories(const int page_index, const int page_limit, int& number_of_records,
                                              const QVector<int>& categories);

    void reduceProductAmount(const int id_p, const int amount);

    void moveAmountFromProducts(const int id_p, const int amount);

    Product* getProductById(const int id_p);

    void addToShoppingCart(const int user_id, const int id_p, const int amount);

    QVector<Product*> getProductFromShoppingCart(const int id_u);

    void updateShoppingCartAmount(const int id_p, const int newAmount);

    void deleteFromShoppingCart(const int id_u, const int id_p);

    void reduceProductAmountInShoppingCart(const int id_u, const int id_p, const int amount);

    void returnProductsToShop(const int id_p, const int amount);
};

#endif // DATABASE_H
