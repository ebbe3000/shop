#include "editpersonaldataform.h"
#include "ui_editpersonaldataform.h"

EditPersonalDataForm::EditPersonalDataForm(const User* user)
    : ui(new Ui::EditPersonalDataForm)
{
    ui->setupUi(this);

    ui->nameEdit->setText(user->getName());
    ui->surnameEdit->setText(user->getSurname());
    ui->emailEdit->setText(user->getEmail());
    ui->passwdEdit->setText(user->getPasswd());

    for (int i = 0; i < 16; ++i) {
        ui->provincesComboBox->setCurrentIndex(i);
        if (ui->provincesComboBox->currentText() == user->getProvince())
            break;
    }

    ui->zipCodeEdit->setText(user->getP_code());
    ui->cityEdit->setText(user->getAddress());
    ui->addressEdit->setText(user->getAddress());

}

EditPersonalDataForm::~EditPersonalDataForm()
{
    delete ui;
}
