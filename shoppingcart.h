#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QWidget>

#include "finalizetransaction.h"
#include "database.h"
#include "loginwithregister.h"

namespace Ui {
class ShoppingCart;
}

/// Class to display shopping cart
class ShoppingCart : public QWidget
{
    Q_OBJECT

public:

    /// Constructor
    ///
    /// @param parent pointer to QWidget, default nullptr
    /// @param db pointer to Database, default nullptr
    /// @param user pointer to User, defaul nullptr
    explicit ShoppingCart(QWidget *parent = nullptr, Database* db = nullptr, User* user = nullptr);
    ~ShoppingCart();

    /// Method loads shopping cart from db for given user
    ///
    /// @param id_u users' id
    /// @return void
    void loadShoppingCartFromDb(const int id_u);

    /// Method adds product to shopping cart, if user is logged in also adds product to shopping cart in database
    ///
    /// @param id_p prodcuts' id
    /// @param amount number of copies of product
    /// @return void
    void addProductToShoppingCart(const int id_p, const int amount);

    /// Method displays products as ProductListElement
    ///
    /// If there's any items is shopping cart displays message "Brak produktow"
    /// @return void
    void loadShoppingCart();

    /// Method sets user, called on log in
    ///
    /// @param user pointer to User
    /// @return void
    void setUser(User* user);

    /// Method clears items in local shopping cart
    ///
    /// @return void
    void clearShoppingCartLocal();

    /// Method deletes item from local shopping cart
    ///
    /// Method is used when not logged user has already item in local shopping
    /// cart and in stored in database shopping cart.
    ///
    /// @return void
    void deleteUsersOwnItems();

    /// Method adds products from local shopping cart to shopping cart
    /// stored in database
    ///
    /// @return void
    void addSelectedProductsToDb();

    /// Method checks if shopping cart is empty
    bool isShoppingCartEmpty();

    /// Method returns deleted/not saved items from shopping cart to database
    ///
    /// @return void
    void returnProductsToShop();

private:
    Ui::ShoppingCart *ui;
    QVector<Product*> shopping_cart_;
    User* user_;
    Database* db_;
    double full_price_;

    /// Method checks if product is in shopping cart
    ///
    /// If product exists method returns pointer to it
    /// otherwise returns nullptr
    Product* checkIfProductInShoppingCart(const int id_p);

    /// Displays FinalizeTransaction
    ///
    /// @return void
    /// @see FinalizeTransaction
    void onFinalizeButtonClicked();


private slots:

    /// Slot deletes product from shopping cart
    ///
    /// @param id_p products' id
    /// @param amount number of copies
    /// @param max_amount number of all copies of product
    void onDeleteProduct(const int id_p, const int amount, const int max_amount);

    /// Slot activates when user decides to finalize transaction and buys products
    ///
    /// Slot before moving products to purchased section checks if they are
    /// still available, if not prints message to refresh shopping cart
    /// If everything is okay then completes purchase and deletes items from
    /// shopping cart and refreshes it.
    /// @param
    void boughtProducts(const QString& delivery_option);

signals:

    /// Signal which causes shopping cart page to refresh
    ///
    /// @return void
    void refreshPage();

    /// Signal which is emited when user logs in while finalizing transaction
    ///
    /// @param user pointer to User which logged in
    void onUserLoggedIn(User* user);
};

#endif // SHOPPINGCART_H
