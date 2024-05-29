#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QWidget>

#include "productlistelement.h"
#include "database.h"

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

private:
    Ui::ShoppingCart *ui;
    QVector<Product*> shopping_cart_;
    User* user_;
    Database* db_;
    double full_price_;

    Product* checkIfProductInShoppingCart(const int id_p);


private slots:
    void onDeleteProduct(const int id_p, const int amount, const int max_amount);

signals:
    void refreshPage();
};

#endif // SHOPPINGCART_H
