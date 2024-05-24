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

    // QString name, surname, email, passwd, province, p_code, city, address;
};

#endif // DATABASE_H
