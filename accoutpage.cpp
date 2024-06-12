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
    QObject::connect(ui->editPersonalDataButton, &QPushButton::clicked, this, &AccoutPage::editPersonalData);
}


AccoutPage::~AccoutPage()
{
    while (ui->productsContainer->count() != 0) {
        QLayoutItem* item = ui->productsContainer->takeAt(0);
        item->widget()->setParent(nullptr);
        ui->productsContainer->removeWidget(item->widget());
        delete item->widget();
    }
    delete ui;
}


void AccoutPage::fillUserData() {
    ui->nameAndSurnameLabel->setText(user_->getName() + " " + user_->getSurname());
    ui->emailLabel->setText(user_->getCity());
    ui->provinceLabel->setText(user_->getProvince());
    ui->cityLabel->setText(user_->getCity());
    ui->addressLabel->setText(user_->getAddress());
}

void AccoutPage::addNewItem() {
    AddProductForm* new_product = new AddProductForm(this, db_, user_);
    QObject::connect(new_product, &AddProductForm::productAdded, this, &AccoutPage::initializeList);
    new_product->show();
}

void AccoutPage::editPersonalData() {
    EditPersonalDataForm* edit_form = new EditPersonalDataForm(user_);
    QObject::connect(edit_form, &EditPersonalDataForm::editUsersData, this, &AccoutPage::editData);
    edit_form->show();
}

void AccoutPage::editData() {
    db_->editUserData(user_);
    fillUserData();
}


void AccoutPage::initializeList() {
    while (ui->productsContainer->count() > 1) {
        QLayoutItem* item = ui->productsContainer->takeAt(0);
        item->widget()->setParent(nullptr);
        ui->productsContainer->removeWidget(item->widget());
        delete item->widget();
    }

    QVector<Product*> list(db_->getClientsProducts(user_->getId()));

    if (list.size() <= 0) {
        QLabel* no_products_label = new QLabel("Brak produktów", this);
        no_products_label->setAlignment(Qt::AlignCenter);
        ui->productsContainer->insertWidget(0, no_products_label);
        return;
    }

    for (auto it : list) {
        ProductListElement* product_list_element = new ProductListElement(this, it, user_, db_->getUserNameAndSurname(it->getIdU()));
        ui->productsContainer->insertWidget(0, product_list_element);
        QObject::connect(product_list_element, &ProductListElement::deleteProduct, [=](const int id_p, const int amount, const int max_amount) {
            emit forwardDeleteProduct(id_p, amount, max_amount);
        });
    }

    fillUserData();
}
