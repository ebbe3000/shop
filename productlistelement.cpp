#include "productlistelement.h"
#include "ui_productlistelement.h"

ProductListElement::ProductListElement(QWidget *parent, const Product& product)
    : QWidget(parent)
    , ui(new Ui::ProductListElement)
{
    ui->setupUi(this);

    QPixmap picture;
    picture.load(product.getImgPath().first());
    ui->imageLabel->setPixmap(picture.scaledToHeight(100));
    ui->nameLabel->setText(product.getName());
    ui->amountNumberLabel->setText(QString::number(product.getAmount()));
    ui->idLabel->setHidden(true);
    ui->idLabel->setText(QString::number(product.getId()));

}

ProductListElement::~ProductListElement()
{
    delete ui;
}
