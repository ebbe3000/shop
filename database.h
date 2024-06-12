#ifndef DATABASE_H
#define DATABASE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>

#include "user.h"
#include "product.h"

/// Class which is responsible for communication with database
class Database
{
    QSqlDatabase db;

public:
    /// Default contructor which connects to database
    ///
    /// It connects to database named shop_db on mysql
    Database();
    ~Database();

    /// Checks if connection to database exists
    ///
    /// @returns bool
    bool isConnected();

    /// Closes database
    ///
    /// @returns void
    void closeDb();

    /// Checks if given email is in database
    ///
    /// @param user pointer to user object
    /// @returns bool
    bool isEmailInDb(const User& user);

    /// Adds user given in parameter to database
    ///
    /// @param user user object
    /// @returns void
    void addUserToDatabase(const User& user);

    /// Checks if user exists in database, if is then param user is filled with data
    ///
    /// @param email given email
    /// @param passwd password
    /// @param user pointer reference to User type object, if users exists user is filled with otehr data of found user
    /// @returns bool
    bool isUserInDb(const QString& email, const QString& passwd, User*& user);

    /// Checks if Product is in database
    ///
    /// Method returns true if product with given id exists in database,
    /// if not return false
    /// @param id_p products' id
    /// @returns bool
    bool isProductInDb(const int id_p);

    /// Collects products of user with given id
    ///
    /// @param id id of user
    /// @returns QVector<Product*> vector of pointers to products
    QVector<Product*> getUsersSellProducts(const int id);

    /// Add product to database
    ///
    /// @param product product which is inserted to database
    /// @returns int id of inserted product from database
    int addProductToDatabase(const Product& product);

    /// Adds path product
    ///
    /// @param id_p products' id
    /// @param path path to photo of product
    /// @returns void
    void addPathToProductToDatabase(const int id_p, const QString& path);

    /// Categories product in database
    ///
    /// @param id_p products's id
    /// @param id_c category id
    void addCategorizedProduct(const int id_p, const int id_c);

    /// Get vector of products of user with given id
    ///
    /// @param id_u users' id
    /// @returns QVector<Product*> vector of pointers to products
    QVector<Product*> getClientsProducts(const int id_u);

    /// Get name and surname of user with give id
    ///
    /// @param id_u users id
    /// @returns QString of name and surname
    QString getUserNameAndSurname(const int id_u);

    /// Delete produt with given id
    ///
    /// @param id_p products' id
    /// @returns void
    void deleteProduct(const int id_p);

    /// Method returns all available products
    ///
    /// @param page_index needed to count correct offset
    /// @param page_limit needed to count correct offset
    /// @param number_of_records needed to correctly block prevpage and nextpage buttons
    /// @returns QVector<Product*> vector of products which are available for sale
    QVector<Product*> getAllProducts(const int page_index, const int page_limit,
                                     int& number_of_records);

    /// Method returns prodcuts which meet the conditions
    ///
    /// @param page_index needed to count correct offset
    /// @param page_limit needed to count correct offset
    /// @param number_of_records needed to correctly block prevpage and nextpage buttons
    /// @param catogies vector of ids of selected categories
    /// @param search_phrase phrase which is search in name of products for sale
    /// @returns QVector<Product*> vector of products which are available for sale and fulfills requirements
    QVector<Product*> getProductsByCategoriesAndName(const int page_index, const int page_limit, int& number_of_records,
                                              const QVector<int>& categories, const QString& search_phrase);

    /// Reduces amount of given ids' product
    ///
    /// This method is used when owner of produt changes amount of products.
    /// This method also removes these products from users shopping carts
    /// @param id_p products' id
    /// @param amount number of how many copies of product are removed
    /// @note even if amount of product is equal to max_amount it doesn't remove product, just reduce amount to 0
    /// @returns void
    void reduceProductAmount(const int id_p, const int amount);

    /// Reduces amount of product
    ///
    /// @param id_p products' id
    /// @param amount amount of reduction
    /// /// @returns void
    void moveAmountFromProducts(const int id_p, const int amount);

    /// Method returns pointer to object of product with given id
    ///
    /// @param id_p id of a product
    /// @returns Product* pointer to product with given id
    Product* getProductById(const int id_p);

    /// Method inserts given amoutn of products to users shopping cart
    ///
    /// @param user_id id of user
    /// @param id_p id of a product
    /// @param amount number of products
    /// @returns void
    void addToShoppingCart(const int user_id, const int id_p, const int amount);

    /// Method gathers all products of users' shopping cart
    ///
    /// @param id_u users' id
    /// @return QVector<Product*> vector of pointer to products from shopping cart
    QVector<Product*> getProductFromShoppingCart(const int id_u);

    /// Method updates amount of product in shopping cart
    ///
    /// @param id_p products' id
    /// @param newAmount new amount
    /// @returns void
    void updateShoppingCartAmount(const int id_p, const int newAmount);

    /// Methods deletes selected product from users shopping cart
    ///
    /// @param id_u users' id
    /// @param id_p products' id
    /// @return void
    void deleteFromShoppingCart(const int id_u, const int id_p);

    /// Method reduces amount of selected product in shopping cart
    ///
    /// @param id_u users' id
    /// @param id_p products' id
    /// @param amount
    void reduceProductAmountInShoppingCart(const int id_u, const int id_p, const int amount);

    /// Add given amount of products to shop.
    ///
    /// Method called when product is removed from shopping cart
    /// @param id_p products' id
    /// @param amount number of returned copies
    /// @return void
    void returnProductsToShop(const int id_p, const int amount);

    /// Method deletes given users shopping cart
    ///
    /// @param id_u
    /// @return void
    void deleteWholeUsersShoppingCart(const int id_u);

    /// Method moves products from shopping cart to purchased
    ///
    /// This method is called when users buy products
    /// @param id_u users' id
    /// @param id_p products' id
    /// @param amount number of copies
    /// @param delivery_option how user decieded to get his product
    /// @param address users' address at the moment of bought
    /// @return void
    void moveShoppingCartToPurchased(const int id_u, const int id_p, const int amount,
                                     const QString& delivery_option, const QString& address);

    /// Method alters user data
    ///
    /// @param user pointer to user with new data
    /// @return void
    void editUserData(User* user);
};

#endif // DATABASE_H
