#ifndef PRODUCTDETAILPAGE_H
#define PRODUCTDETAILPAGE_H

#include <QDialog>

#include "product.h"
#include "user.h"
#include "multipictures.h"

namespace Ui {
class ProductDetailPage;
}

class ProductDetailPage : public QDialog
{
    Q_OBJECT

public:
    explicit ProductDetailPage(const Product* product = nullptr, const User* user = nullptr,
                               QString&& full_name_of_seller = "Error", const int shopping_cart_mode = 0);
    ~ProductDetailPage();

private:
    Ui::ProductDetailPage *ui;
    const Product* product_;
    const User* user_;


private slots:
    void onDeleteButtonClicked();
    void onAddToCartButton();
    // void onDeleteFromShoppingCartButton();

signals:

    void deleteProduct(const int amount);
    void addProductToShoppingCart(const int id_p, const int amount);

};

#endif // PRODUCTDETAILPAGE_H
