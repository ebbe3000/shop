#ifndef PRODUCTLISTELEMENT_H
#define PRODUCTLISTELEMENT_H

#include <QWidget>
#include <QPixmap>
#include <QMessageBox>
#include <QPainter>
#include <QWindow>

#include "productdetailpage.h"

namespace Ui {
class ProductListElement;
}

/// Class to display products in list
class ProductListElement : public QWidget
{
    Q_OBJECT

public:
    /// Constructor
    ///
    /// @param parent pointer to QWidget, default nullptr
    /// @param prodcut const pointer to product element, default nullptr
    /// @param user const pointer to user, default nullptr
    /// @param full_name_of_seller name of seller, default "Error"
    /// @param shopping_cart_mode display mode, default 0
    explicit ProductListElement(QWidget *parent = nullptr, const Product* product = nullptr,
                                const User* user = nullptr, QString&& full_name_of_seller = "Error", const int shopping_cart_mode = 0);
    ~ProductListElement();

private:
    Ui::ProductListElement *ui;
    const Product* product_;
    const User* user_;
    const int shopping_cart_mode_;


private slots:

    /// Slot displays ProductDetailPage
    ///
    /// @return void
    /// @see ProductDetailPage
    /// @return void
    void onShowButtonClicked();

    /// Slot emits signal deleteProduct, if no amount given it is set to 0
    ///
    /// @param amount number of deleted copies
    /// @return void
    void onDeleteButtonClicked(int amount = 0);

    /// Slot emits signal addProductToShoppingCart
    ///
    /// @param id_p products' id
    /// @param amount number of copies of product
    /// @return void
    void forwardAddProductToShoppingCart(const int id_p, const int amount);

signals:

    /// Signal emited on product deletion
    ///
    /// @param id_p products' id
    /// @param amount number of copies of product
    /// @param max_amount number of all copies
    /// @return void
    void deleteProduct(const int id_p, const int amount, const int max_amount);


    /// Signal emited on adding product to shopping cart
    ///
    /// @param id_p product id
    /// @param amount number of copies of product
    void addProductToShoppingCart(const int id_p, const int amount);

};

#endif // PRODUCTLISTELEMENT_H
