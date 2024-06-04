#include "finalizetransaction.h"
#include "ui_finalizetransaction.h"

#include <QDebug>

FinalizeTransaction::FinalizeTransaction(const User* user, const QVector<Product*>& products, const double price)
    : ui(new Ui::FinalizeTransaction)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->lhdRadioButton->setChecked(true);
    ui->nameAndSurnameLabel->setText(user->getName() + " " + user->getSurname());
    ui->addressLabel->setText(user->getAddress());
    ui->zipCodeLabel->setText(user->getP_code());
    ui->cityLabel->setText(user->getCity());
    ui->emailLabel->setText(user->getEmail());

    ui->priceDoubleLabel->setText(QString::number(price));

    QObject::connect(ui->confirmButton, &QPushButton::clicked, this, &FinalizeTransaction::onConfirmButtonClicked);

    for (auto it : products) {
        ProductListElement* product_list_element = new ProductListElement(this, it, user, "", 2);
        ui->productsLayout->addWidget(product_list_element);
        ui->productsLayout->setAlignment(product_list_element, Qt::AlignTop);
    }
}

FinalizeTransaction::~FinalizeTransaction()
{
    delete ui;
}

void FinalizeTransaction::onConfirmButtonClicked() {
    emit boughtProducts(ui->deliverGroup->checkedButton()->text());
    this->close();
}
