#include "accoutpage.h"
#include "ui_accoutpage.h"


AccoutPage::AccoutPage(QWidget *parent, Database* db, User* user)
    : QWidget(parent)
    , ui(new Ui::AccoutPage)
    , db_(db)
    , user_(user)
{
    ui->setupUi(this);
    QObject::connect(ui->addNewItemButton, &QPushButton::clicked, this, &AccoutPage::addNewItem);
}

AccoutPage::~AccoutPage()
{
    delete ui;
}

void AccoutPage::fillUserData() {
    ui->nameAndSurnameLabel->setText(user_->getName() + " " + user_->getSurname());
    ui->emailLabel->setText(user_->getCity());
    ui->provinceLabel->setText(user_->getProvince());
    ui->cityLabel->setText(user_->getCity());
    ui->addressLabel->setText(user_->getAddress());

    // skonczyc po dodaniu funkcji dodawania rzeczy
}

void AccoutPage::addNewItem() {
    AddProductForm* new_product = new AddProductForm(this, db_, user_);
    new_product->show();
}
