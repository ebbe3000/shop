#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QWidget>

#include "finalizetransaction.h"
#include "database.h"
#include "loginwithregister.h"

namespace Ui {
class ShoppingCart;
}

class ShoppingCart : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingCart(QWidget *parent = nullptr, Database* db = nullptr, User* user = nullptr);
    ~ShoppingCart();

    void loadShoppingCartFromDb(const int id_u);

    void addProductToShoppingCart(const int id_p, const int amount);

    void loadShoppingCart();

    void setUser(User* user);

    void clearShoppingCartLocal();

    void deleteUsersOwnItems();

    void addSelectedProductsToDb();

    bool isShoppingCartEmpty();

    void returnProductsToShop();

private:
    Ui::ShoppingCart *ui;
    QVector<Product*> shopping_cart_;
    User* user_;
    Database* db_;
    double full_price_;

    Product* checkIfProductInShoppingCart(const int id_p);

    void onFinalizeButtonClicked();


private slots:
    void onDeleteProduct(const int id_p, const int amount, const int max_amount);

    void boughtProducts(const QString& delivery_option);

signals:
    void refreshPage();

    void onUserLoggedIn(User* user);
};

#endif // SHOPPINGCART_H
