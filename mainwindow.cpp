#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db_(), user_(nullptr)
    , account_page(nullptr)
{
    ui->setupUi(this);
    ui->nameBox->setHidden(true);
    ui->stackedWidget->setCurrentIndex(0);

    guestUiSetup();

    QObject::connect(ui->nameSignInButton, &QPushButton::clicked, this, &MainWindow::userButtonClicked);
    QObject::connect(ui->iconSignInButton, &QPushButton::clicked, this, &MainWindow::userButtonClicked);
    QObject::connect(ui->nameLogOutButton, &QPushButton::clicked, this, &MainWindow::logOut);
    QObject::connect(ui->iconLogOutButton, &QPushButton::clicked, this, &MainWindow::logOut);
    QObject::connect(ui->nameAccountButton, &QPushButton::clicked, this, &MainWindow::showAccount);
    QObject::connect(ui->iconAccountButton, &QPushButton::clicked, this, &MainWindow::showAccount);
    QObject::connect(ui->nameShoppingCartButton, &QPushButton::clicked, this, &MainWindow::showShoppingCart);
    QObject::connect(ui->iconShoppingCartButton, &QPushButton::clicked, this, &MainWindow::showShoppingCart);
    QObject::connect(ui->iconProductsButton, &QPushButton::clicked, this, &MainWindow::productsButtonClicked);
    QObject::connect(ui->nameProductsButton, &QPushButton::clicked, this, &MainWindow::productsButtonClicked);

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
    }
}


MainWindow::~MainWindow()
{
    db_.closeDb();
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
    LogInWithRegister* log_win = new LogInWithRegister(this, &db_);
    QObject::connect(log_win, &LogInWithRegister::userLoggedIn, this, &MainWindow::onUserLoggedIn);
    log_win->show();
}


void MainWindow::onUserLoggedIn(User* user) {
    user_ = user;

    account_page = new AccoutPage(this, &db_, user_);
    ui->stackedWidget->insertWidget(2, account_page);
    userUiSetup();
}


void MainWindow::logOut() {
    delete user_;
    guestUiSetup();
}


void MainWindow::showShoppingCart() {
    qDebug() << "shopping cart";
}

void MainWindow::showAccount() {
    account_page->fillUserData();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::productsButtonClicked() {
    // products reload function

    ui->stackedWidget->setCurrentIndex(0);
}
