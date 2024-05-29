#ifndef PRODUCTLISTELEMENT_H
#define PRODUCTLISTELEMENT_H

#include <QWidget>
#include <QPixmap>
#include <QMessageBox>

#include "productdetailpage.h"

namespace Ui {
class ProductListElement;
}

class ProductListElement : public QWidget
{
    Q_OBJECT

public:
    explicit ProductListElement(QWidget *parent = nullptr, const Product* product = nullptr,
                                const User* user = nullptr, QString&& full_name_of_seller = "Error", const int shopping_cart_mode = 0);
    ~ProductListElement();

private:
    Ui::ProductListElement *ui;
    const Product* product_;
    const User* user_;
    const int shopping_cart_mode_;


private slots:
    void onShowButtonClicked();

    void onDeleteButtonClicked(int amount = 0);

    void forwardAddProductToShoppingCart(const int id_p, const int amount);

signals:
    void deleteProduct(const int id_p, const int amount, const int max_amount);

    void addProductToShoppingCart(const int id_p, const int amount);

};

#endif // PRODUCTLISTELEMENT_H
