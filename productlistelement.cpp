#include "productlistelement.h"
#include "ui_productlistelement.h"

ProductListElement::ProductListElement(QWidget *parent, const Product* product, const User* user,
                                       QString&& full_name_of_seller, const int shopping_cart_mode)
    : QWidget(parent)
    , ui(new Ui::ProductListElement)
    , product_(product)
    , user_(user)
    , shopping_cart_mode_(shopping_cart_mode)
{
    ui->setupUi(this);

    QPixmap picture;
    picture.load(product_->getImgPath().first());
    ui->imageLabel->setPixmap(picture.scaledToHeight(100));
    ui->nameLabel->setText(product_->getName());
    ui->amountNumberLabel->setText(QString::number(product_->getAmount()));
    ui->fullNameLabel->setHidden(true);
    ui->fullNameLabel->setText(full_name_of_seller);
    if (user_ == nullptr || user_->getId() != product_->getIdU())
        ui->deleteProductButton->setHidden(true);

    QObject::connect(ui->showProductButton, &QPushButton::clicked, this, &ProductListElement::onShowButtonClicked);
    QObject::connect(ui->deleteProductButton, &QPushButton::clicked, this, &ProductListElement::onDeleteButtonClicked);

}


ProductListElement::~ProductListElement()
{
    delete ui;
}


void ProductListElement::onShowButtonClicked() {
    ProductDetailPage* product_detail_page = new ProductDetailPage(product_, user_, ui->fullNameLabel->text(), shopping_cart_mode_);
    QObject::connect(product_detail_page, &ProductDetailPage::deleteProduct, this, &ProductListElement::onDeleteButtonClicked);
    QObject::connect(product_detail_page, &ProductDetailPage::addProductToShoppingCart, this, &ProductListElement::forwardAddProductToShoppingCart);
    product_detail_page->show();
}


void ProductListElement::onDeleteButtonClicked(int amount) {
    QMessageBox::about(this, "Info", "Usunąłeś produkt");
    if (amount == 0)
        amount = product_->getAmount();
    emit deleteProduct(product_->getId(), amount, product_->getAmount());
}

void ProductListElement::forwardAddProductToShoppingCart(const int id_p, const int amount) {
    QMessageBox::about(this, "Info", "Produkt dodano do koszyka");
    emit addProductToShoppingCart(id_p, amount);
}
