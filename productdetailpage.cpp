#include "productdetailpage.h"
#include "ui_productdetailpage.h"

ProductDetailPage::ProductDetailPage(const Product* product, const User* user, QString&& full_name_of_seller, const int shopping_cart_mode)
    : ui(new Ui::ProductDetailPage)
    , product_(product)
    , user_(user)
    //, shopping_cart_mode_(shopping_cart_mode)
{
    if (product == nullptr)
        throw "Cannot display product details without pointer to the product";
    ui->setupUi(this);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->amountSpinBox->setMaximum(product_->getAmount());
    ui->availableAmountLabel->setText(QString::number(product_->getAmount()));
    ui->deleteProductButton->setHidden(true);
    ui->addToCartButton->setHidden(true);
    //ui->deleteFromShoppingCartButton->setHidden(true);

    if (shopping_cart_mode)
        ui->deleteProductButton->setHidden(false);
    else
        if (user != nullptr)
            if (user->getId() != product->getIdU())
                ui->addToCartButton->setHidden(false);
            else
                ui->deleteProductButton->setHidden(false);
        else
            ui->addToCartButton->setHidden(false);

    QObject::connect(ui->deleteProductButton, &QPushButton::clicked, this, &ProductDetailPage::onDeleteButtonClicked);
    QObject::connect(ui->addToCartButton, &QPushButton::clicked, this, &ProductDetailPage::onAddToCartButton);
    //QObject::connect(ui->deleteFromShoppingCartButton, &QPushButton, this, &ProductDetailPage::onDeleteFromShoppingCartButton);

    ui->sellerLabel->setText(full_name_of_seller);
    ui->addDateLabel->setText(product->getAddDate());
    MultiPictures* pics = new MultiPictures(this, product->getImgPath());
    ui->leftVLayout->insertWidget(0, pics);
    ui->addDateLabel->setText(product->getAddDate());
    ui->productNameLabel->setText(product->getName());
    ui->productPriceNumLabel->setText(QString::number(product->getPrice()) + " zł");
}

ProductDetailPage::~ProductDetailPage() {
    delete ui;
}


void ProductDetailPage::onDeleteButtonClicked() {
    emit deleteProduct(ui->amountSpinBox->value());
    this->close();
}


void ProductDetailPage::onAddToCartButton() {
    emit addProductToShoppingCart(product_->getId(), ui->amountSpinBox->value());
    this->close();
}
