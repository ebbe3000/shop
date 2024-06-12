#ifndef PRODUCTDETAILPAGE_H
#define PRODUCTDETAILPAGE_H

#include <QDialog>

#include "product.h"
#include "user.h"
#include "multipictures.h"

namespace Ui {
class ProductDetailPage;
}

/// Class which displays details about products
class ProductDetailPage : public QDialog
{
    Q_OBJECT

public:
    /// Constructor
    ///
    /// @param product cosnt pointer to product, defaul nullptr
    /// @param user const pointer to user, default nullptr
    /// @param full_name_of_seller name of seller, defaul "Error"
    /// @param shopping_cart_mode if product is displayed from shopping cart, default 0
    explicit ProductDetailPage(const Product* product = nullptr, const User* user = nullptr,
                               QString&& full_name_of_seller = "Error", const int shopping_cart_mode = 0);
    ~ProductDetailPage();

private:
    Ui::ProductDetailPage *ui;
    const Product* product_;
    const User* user_;


private slots:

    /// Emits signal on delete product button clicked
    ///
    /// @return void
    void onDeleteButtonClicked();

    /// Emits signal to delete product button clicked
    void onAddToCartButton();

signals:

    /// Signal emitted on product deleletion
    ///
    /// @param amount number of copies deleted
    /// @return void
    void deleteProduct(const int amount);

    /// Signal emitted on adding product to shopping cart
    ///
    /// @param id_p products' id
    /// @param amount number of copies added to shopping cart
    void addProductToShoppingCart(const int id_p, const int amount);

};

#endif // PRODUCTDETAILPAGE_H
