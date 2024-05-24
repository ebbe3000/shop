#ifndef PRODUCTLISTELEMENT_H
#define PRODUCTLISTELEMENT_H

#include <QWidget>
#include <QPixmap>

#include "product.h"

namespace Ui {
class ProductListElement;
}

class ProductListElement : public QWidget
{
    Q_OBJECT

public:
    explicit ProductListElement(QWidget *parent = nullptr, const Product& product = Product());
    ~ProductListElement();

private:
    Ui::ProductListElement *ui;
};

#endif // PRODUCTLISTELEMENT_H
