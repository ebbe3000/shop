#include "shoppingcart.h"
#include "ui_shoppingcart.h"

#include <QDebug>

ShoppingCart::ShoppingCart(QWidget *parent, Database* db, User* user)
    : QWidget(parent)
    , ui(new Ui::ShoppingCart)
    , db_(db)
    , user_(user)
    , full_price_(0)
{
    ui->setupUi(this);





    QObject::connect(ui->finalizeButton, &QPushButton::clicked, this, &ShoppingCart::onFinalizeButtonClicked);
    loadShoppingCart();
}


ShoppingCart::~ShoppingCart()
{
    for (auto it : shopping_cart_)
        delete it;

    delete ui;
}


void ShoppingCart::loadShoppingCart() {
    while (ui->shoppingCartProductsLayout->count() > 0) {
        QLayoutItem* item = ui->shoppingCartProductsLayout->takeAt(0);
        item->widget()->setParent(nullptr);
        ui->shoppingCartProductsLayout->removeWidget(item->widget());
        delete item->widget();
    }
    full_price_ = 0;

    if (shopping_cart_.size() <= 0) {
        // if no products
        QLabel* no_products_label = new QLabel("Brak produktów", this);
        ui->shoppingCartProductsLayout->addWidget(no_products_label);
        ui->priceLabel->setText(QString::number(full_price_) + " zł");
        ui->finalizeButton->setDisabled(true);
        return;
    }

    ui->finalizeButton->setDisabled(false);
    for (auto it : shopping_cart_) {
        ProductListElement* product_list_element = new ProductListElement(this, it, user_, db_->getUserNameAndSurname(it->getIdU()), 1);
        full_price_ += it->getPrice() * it->getAmount();
        ui->shoppingCartProductsLayout->addWidget(product_list_element);
        ui->shoppingCartProductsLayout->setAlignment(product_list_element, Qt::AlignTop);
        QObject::connect(product_list_element, &ProductListElement::deleteProduct, this, &ShoppingCart::onDeleteProduct);
    }
    ui->priceLabel->setText(QString::number(full_price_) + " zł");
}


void ShoppingCart::addProductToShoppingCart(const int id_p, const int amount) {
    Product* product = nullptr;
    if (product = checkIfProductInShoppingCart(id_p)) {
        product->setAmount(product->getAmount() + amount);
        db_->updateShoppingCartAmount(id_p, product->getAmount());
    }
    else {
        product = db_->getProductById(id_p);
        product->setAmount(amount);
        shopping_cart_.push_back(product);
        if (user_ != nullptr)
            db_->addToShoppingCart(user_->getId(), id_p, amount);
    }
    db_->moveAmountFromProducts(id_p, amount);
    emit refreshPage();
}


void ShoppingCart::loadShoppingCartFromDb(const int id_u) {
    QVector<Product*> tmp = db_->getProductFromShoppingCart(id_u);
    for (auto it : tmp)
        shopping_cart_.push_back(it);
}


void ShoppingCart::setUser(User* user) {
    user_ = user;
}


Product* ShoppingCart::checkIfProductInShoppingCart(const int id_p) {
    for (auto it : shopping_cart_)
        if (it->getId() == id_p)
            return it;
    return nullptr;
}


void ShoppingCart::clearShoppingCartLocal() {
    for (auto it : shopping_cart_)
        delete it;
    shopping_cart_.clear();
}


void ShoppingCart::onDeleteProduct(const int id_p, const int amount, const int max_amount) {
    QVector<Product*>::iterator product_position;
    for (QVector<Product*>::iterator it = shopping_cart_.begin(); it != shopping_cart_.end(); ++it)
        if ((*it)->getId() == id_p) {
            product_position = it;
            break;
        }
    if (amount == max_amount) {
        if (product_position == shopping_cart_.end())
            return;
        delete *product_position;
        shopping_cart_.erase(product_position);

        if (user_ != nullptr)
            db_->deleteFromShoppingCart(user_->getId(), id_p);
    }
    else {
        (*product_position)->setAmount((*product_position)->getAmount() - amount);

        if (user_ != nullptr)
            db_->reduceProductAmountInShoppingCart(user_->getId(), id_p, amount);
    }

    db_->returnProductsToShop(id_p, amount);

    loadShoppingCart();
}

void ShoppingCart::boughtProducts(const QString& delivery_option) {
    int size = shopping_cart_.size();
    for (QVector<Product*>::const_iterator it = shopping_cart_.begin(); it != shopping_cart_.end(); ++it)
        if (!db_->isProductInDb((*it)->getId())) {
            delete *it;
            shopping_cart_.erase(it);
            if (it == shopping_cart_.end())
                break;
        }

    if (!(size == shopping_cart_.size())) {
        QMessageBox::about(this, "Info", "Produkt niedostępny, odswierz koszyk");
        return;
    }

    for (auto it : shopping_cart_)
        db_->moveShoppingCartToPurchased(user_->getId(), it->getId(), it->getAmount(), delivery_option, user_->getCity() + " " + user_->getAddress());

    db_->deleteWholeUsersShoppingCart(user_->getId());

    for (auto it : shopping_cart_)
        delete it;

    shopping_cart_.clear();
    QMessageBox::about(this, "Info", "Produkt zamowiony");
    loadShoppingCart();

}


void ShoppingCart::onFinalizeButtonClicked() {
    if (user_ == nullptr) {
        LogInWithRegister* log_win = new LogInWithRegister(db_);
        QObject::connect(log_win, &LogInWithRegister::userLoggedIn, [=](User* user) {
            emit onUserLoggedIn(user);
        });
        log_win->show();
        return;
    }
    FinalizeTransaction* fin_trans = new FinalizeTransaction(user_, shopping_cart_, full_price_);
    QObject::connect(fin_trans, &FinalizeTransaction::boughtProducts, this, &ShoppingCart::boughtProducts);
    fin_trans->show();
}


void ShoppingCart::deleteUsersOwnItems() {
    for (QVector<Product*>::iterator it = shopping_cart_.begin(); it != shopping_cart_.end(); ++it)
        if ((*it)->getIdU() == user_->getId()) {
            db_->returnProductsToShop((*it)->getId(), (*it)->getAmount());
            delete *it;
            shopping_cart_.erase(it);
            if (it == shopping_cart_.end())
                break;
        }
    loadShoppingCart();
}

void ShoppingCart::addSelectedProductsToDb() {
    for (auto it : shopping_cart_)
        db_->addToShoppingCart(user_->getId(), it->getId(), it->getAmount());
}

bool ShoppingCart::isShoppingCartEmpty() {
    if (shopping_cart_.isEmpty())
        return true;
    return false;
}

void ShoppingCart::returnProductsToShop() {
    for (auto it : shopping_cart_)
        db_->returnProductsToShop(it->getId(), it->getAmount());
}
