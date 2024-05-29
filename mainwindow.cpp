#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db_(), user_(nullptr)
    , account_page_(nullptr)
    , page_size_(10)
    , product_page_index_(0)
    , records_amount_(0)
{
    ui->setupUi(this);
    ui->nameBox->setHidden(true);
    ui->stackedWidget->setCurrentIndex(0);
    ui->checkboxArea->setHidden(true);
    ui->mainPrevButton->setDisabled(true);

    guestUiSetup();

    QObject::connect(ui->nameSignInButton, &QPushButton::clicked, this, &MainWindow::userButtonClicked);
    QObject::connect(ui->iconSignInButton, &QPushButton::clicked, this, &MainWindow::userButtonClicked);
    QObject::connect(ui->nameLogOutButton, &QPushButton::clicked, this, &MainWindow::logOut);
    QObject::connect(ui->iconLogOutButton, &QPushButton::clicked, this, &MainWindow::logOut);
    QObject::connect(ui->nameAccountButton, &QPushButton::clicked, this, &MainWindow::showAccount);
    QObject::connect(ui->iconAccountButton, &QPushButton::clicked, this, &MainWindow::showAccount);
    QObject::connect(ui->iconProductsButton, &QPushButton::clicked, this, &MainWindow::productsButtonClicked);
    QObject::connect(ui->nameProductsButton, &QPushButton::clicked, this, &MainWindow::productsButtonClicked);
    QObject::connect(ui->categoriesButton, &QPushButton::clicked, this, &MainWindow::categoriesButtonClicked);
    QObject::connect(ui->mainPrevButton, &QPushButton::clicked, this, &MainWindow::mainPrevButtonClicked);
    QObject::connect(ui->mainNextButton, &QPushButton::clicked, this, &MainWindow::mainNextButtonClicked);
    QObject::connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchButtonClicked);
    QObject::connect(ui->clearCategoriesButton, &QPushButton::clicked, this, &MainWindow::clearCategoriesButtonsClicked);


    if (!db_.isConnected()) {
        ui->stackedWidget->setCurrentIndex(1);

        ui->iconSignInButton->setEnabled(false);
        ui->nameSignInButton->setEnabled(false);

        ui->nameShoppingCartButton->setEnabled(false);
        ui->iconShoppingCartButton->setEnabled(false);

        ui->mainNextButton->setEnabled(false);
        ui->mainPrevButton->setEnabled(false);

        ui->mainNextButton->setHidden(true);
        ui->mainPrevButton->setHidden(true);

        ui->iconProductsButton->setDisabled(true);
        ui->nameProductsButton->setDisabled(true);
        return;
    }

    shopping_cart_page_ = new ShoppingCart(this, &db_, user_);
    QObject::connect(ui->iconShoppingCartButton, &QPushButton::clicked, this, &MainWindow::onShoppingCartButtonClicked);
    QObject::connect(ui->nameShoppingCartButton, &QPushButton::clicked, this, &MainWindow::onShoppingCartButtonClicked);
    QObject::connect(shopping_cart_page_, &ShoppingCart::refreshPage, [=]() {
        loadProductList();
    });
    ui->stackedWidget->insertWidget(2, shopping_cart_page_);

    loadProductList();
}


MainWindow::~MainWindow()
{
    db_.closeDb();
    delete shopping_cart_page_;
    delete account_page_;
    delete user_;
    delete ui;
}


void MainWindow::guestUiSetup() {
    enableAndShowButton(ui->iconSignInButton);

    enableAndShowButton(ui->nameSignInButton);

    disableAndHideButton(ui->iconLogOutButton);

    disableAndHideButton(ui->nameLogOutButton);

    disableAndHideButton(ui->iconAccountButton);

    disableAndHideButton(ui->nameAccountButton);

    enableAndShowButton(ui->iconShoppingCartButton);

    enableAndShowButton(ui->nameShoppingCartButton);

    enableAndShowButton(ui->iconProductsButton);

    enableAndShowButton(ui->nameProductsButton);
}


void MainWindow::userUiSetup() {
    disableAndHideButton(ui->iconSignInButton);

    disableAndHideButton(ui->nameSignInButton);

    enableAndShowButton(ui->iconLogOutButton);

    enableAndShowButton(ui->nameLogOutButton);

    enableAndShowButton(ui->iconAccountButton);

    enableAndShowButton(ui->nameAccountButton);
}


void MainWindow::disableAndHideButton(QPushButton* button) {
    button->setDisabled(true);
    button->setHidden(true);
}


void MainWindow::enableAndShowButton(QPushButton* button) {
    button->setDisabled(false);
    button->setHidden(false);
}


void MainWindow::userButtonClicked() {
    LogInWithRegister* log_win = new LogInWithRegister(&db_);
    QObject::connect(log_win, &LogInWithRegister::userLoggedIn, this, &MainWindow::onUserLoggedIn);
    log_win->show();
}


void MainWindow::mainNextButtonClicked() {
    ++product_page_index_;
    ui->mainPrevButton->setDisabled(false);
    loadProductList();
}


void MainWindow::mainPrevButtonClicked() {
    --product_page_index_;
    if (product_page_index_ == 0)
        ui->mainPrevButton->setDisabled(true);
    ui->mainNextButton->setDisabled(false);
    loadProductList();
}


void MainWindow::categoriesButtonClicked() {
    ui->checkboxArea->isHidden() ? ui->checkboxArea->setHidden(false) : ui->checkboxArea->setHidden(true);
}


void MainWindow::searchButtonClicked() {
    product_page_index_ = 0;
    ui->mainPrevButton->setDisabled(true);
    getSelectedCategories();
    loadProductList();
}

void MainWindow::onShoppingCartButtonClicked() {
    ui->stackedWidget->setCurrentIndex(2);
    shopping_cart_page_->loadShoppingCart();
}


void MainWindow::clearCategoriesButtonsClicked() {
    QList<QCheckBox*> list = ui->scrollAreaWidgetContents_2->findChildren<QCheckBox*>();
    for (auto it : list)
        it->setChecked(false);

    selected_categories_.clear();
}


void MainWindow::onUserLoggedIn(User* user) {
    user_ = user;

    account_page_ = new AccoutPage(this, &db_, user_);
    QObject::connect(account_page_, &AccoutPage::forwardDeleteProduct, this, &MainWindow::deleteProduct);
    ui->stackedWidget->insertWidget(3, account_page_);
    userUiSetup();
    loadProductList();
    shopping_cart_page_->setUser(user_);
    shopping_cart_page_->loadShoppingCartFromDb(user_->getId());
}


void MainWindow::logOut() {
    ui->stackedWidget->setCurrentIndex(0);
    account_page_->setParent(nullptr);
    ui->stackedWidget->removeWidget(account_page_);
    delete account_page_;
    account_page_ = nullptr;
    delete user_;
    user_ = nullptr;
    guestUiSetup();
    shopping_cart_page_->clearShoppingCartLocal();
    loadProductList();
}


void MainWindow::showAccount() {
    account_page_->fillUserData();
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::productsButtonClicked() {
    loadProductList();

    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::deleteProduct(const int id_p, const int amount, const int max_amount) {
    if (amount >= max_amount)
        db_.deleteProduct(id_p);
    else
        db_.reduceProductAmount(id_p, amount);
    if (account_page_ != nullptr)
        account_page_->initializeList();

    loadProductList();
}


void MainWindow::getSelectedCategories() {
    selected_categories_.clear();

    if (ui->electronicsCheckbox->isChecked())
        selected_categories_.push_back(1);
    if (ui->fashionCheckbox->isChecked())
        selected_categories_.push_back(2);
    if (ui->houseAndGardenCheckbox->isChecked())
        selected_categories_.push_back(3);
    if (ui->beautyCheckbox->isChecked())
        selected_categories_.push_back(4);
    if (ui->sportCheckbox->isChecked())
        selected_categories_.push_back(5);
    if (ui->automotiveCheckbox->isChecked())
        selected_categories_.push_back(6);
    if (ui->supermarketCheckbox->isChecked())
        selected_categories_.push_back(7);
    if (ui->healthCheckbox->isChecked())
        selected_categories_.push_back(8);
    if (ui->artCheckbox->isChecked())
        selected_categories_.push_back(9);
}


void MainWindow::loadProductList() {
    // clear old products
    while (ui->productsContainer->count() > 0) {
        QLayoutItem* item = ui->productsContainer->takeAt(0);
        item->widget()->setParent(nullptr);
        ui->productsContainer->removeWidget(item->widget());
        delete item->widget();
    }

    QVector<Product*> products;

    if (selected_categories_.isEmpty())
        // show products without specifying category
        products = db_.getAllProducts(product_page_index_, page_size_, records_amount_);
    else
        // show categorized products
        products = db_.getProductsByCategories(product_page_index_, page_size_, records_amount_, selected_categories_);


    if (records_amount_ <= 0) {
        // if no products
        QLabel* no_products_label = new QLabel("Brak produktów", this);
        ui->productsContainer->addWidget(no_products_label);
        return;
    }

    for (auto it : products) {
        ProductListElement* product_list_element = new ProductListElement(this, it, user_, db_.getUserNameAndSurname(it->getIdU()));
        ui->productsContainer->addWidget(product_list_element);
        QObject::connect(product_list_element, &ProductListElement::deleteProduct, this, &MainWindow::deleteProduct);
        QObject::connect(product_list_element, &ProductListElement::addProductToShoppingCart, this, &MainWindow::addProductToShoppingCart);
    }

    if (records_amount_ <= (product_page_index_ + 1) * page_size_)
        ui->mainNextButton->setDisabled(true);
    else
        ui->mainNextButton->setDisabled(false);
}


void MainWindow::addProductToShoppingCart(const int id_p, const int amount) {
    shopping_cart_page_->addProductToShoppingCart(id_p, amount);
    loadProductList();
}
