#include "editpersonaldataform.h"
#include "ui_editpersonaldataform.h"

EditPersonalDataForm::EditPersonalDataForm(User* user)
    : ui(new Ui::EditPersonalDataForm)
    , user_(user)
    , name_(user->getName()), surname_(user->getSurname())
    , email_(user->getEmail()), passwd_(user->getPasswd())
    , province_(user->getProvince()), zip_code_(user->getP_code())
    , city_(user->getCity()), address_(user->getAddress())
    , wrong_data_edit_("background-color: red;")
{
    ui->setupUi(this);
    setModal(true);
    for (int i = 0; i < 7; ++i)
        ok[i] = true;

    ui->errorLabel->setHidden(true);

    ui->nameEdit->setText(name_);
    ui->surnameEdit->setText(surname_);
    ui->emailEdit->setText(email_);
    ui->passwdEdit->setText(passwd_);

    for (int i = 0; i < 16; ++i) {
        ui->provincesComboBox->setCurrentIndex(i);
        if (ui->provincesComboBox->currentText() == province_)
            break;
    }

    ui->zipCodeEdit->setText(zip_code_);
    ui->cityEdit->setText(city_);
    ui->addressEdit->setText(address_);

    QObject::connect(new FocusWatcher(ui->nameEdit), &FocusWatcher::focusChanged, this, &EditPersonalDataForm::checkName);
    QObject::connect(new FocusWatcher(ui->surnameEdit), &FocusWatcher::focusChanged, this, &EditPersonalDataForm::checkSurname);
    QObject::connect(new FocusWatcher(ui->emailEdit), &FocusWatcher::focusChanged, this, &EditPersonalDataForm::checkEmail);
    QObject::connect(new FocusWatcher(ui->passwdEdit), &FocusWatcher::focusChanged, this, &EditPersonalDataForm::checkPasswd);
    QObject::connect(new FocusWatcher(ui->zipCodeEdit), &FocusWatcher::focusChanged, this, &EditPersonalDataForm::checkZipCode);
    QObject::connect(new FocusWatcher(ui->cityEdit), &FocusWatcher::focusChanged, this, &EditPersonalDataForm::checkCity);
    QObject::connect(new FocusWatcher(ui->addressEdit), &FocusWatcher::focusChanged, this, &EditPersonalDataForm::checkAddress);
    QObject::connect(ui->confirmButton, &QPushButton::clicked, this, &EditPersonalDataForm::confirmButtonClicked);
}


EditPersonalDataForm::~EditPersonalDataForm()
{
    delete ui;
}


void EditPersonalDataForm::checkName() {
    name_ = ui->nameEdit->text();

    if (name_ == "" || name_[0].isDigit() || name_[0].isLower()) {
        ok[0] = false;
        ui->nameEdit->setStyleSheet(wrong_data_edit_);
        return;
    }
    else
        for (auto it = name_.begin() + 1; it != name_.end(); ++it)
            if (it->isUpper() || it->isDigit()) {
                ok[0] = false;
                ui->nameEdit->setStyleSheet(wrong_data_edit_);
                return;
            }

    ui->nameEdit->setStyleSheet("");
    ok[0] = true;
}


void EditPersonalDataForm::checkSurname() {
    surname_ = ui->surnameEdit->text();

    if (surname_ == "" || surname_[0].isDigit() || surname_[0].isLower()) {
        ok[1] = false;
        ui->surnameEdit->setStyleSheet(wrong_data_edit_);
        return;
    }
    else
        for (auto it = surname_.begin() + 1; it != surname_.end(); ++it)
            if (it->isUpper() || it->isDigit()) {
                ok[1] = false;
                ui->surnameEdit->setStyleSheet(wrong_data_edit_);
                return;
            }

    ui->surnameEdit->setStyleSheet("");
    ok[1] = true;
}


void EditPersonalDataForm::checkEmail() {
    email_ = ui->emailEdit->text();

    if (email_ == "" || !email_.contains("@", Qt::CaseInsensitive) || email_.size() < 3) {
        ok[2] = false;
        ui->emailEdit->setStyleSheet(wrong_data_edit_);
        return;
    }

    ui->emailEdit->setStyleSheet("");
    ok[2] = true;
}


void EditPersonalDataForm::checkPasswd() {
    passwd_ = ui->passwdEdit->text();

    if (passwd_ == "" || passwd_.size() < 5) {
        ok[3] = false;
        ui->passwdEdit->setStyleSheet(wrong_data_edit_);
        return;
    }

    ui->passwdEdit->setStyleSheet("");
    ok[3] = true;
}


void EditPersonalDataForm::checkZipCode() {
    zip_code_ = ui->zipCodeEdit->text();

    if (zip_code_.size() < 6) {
        ok[4] = false;
        ui->zipCodeEdit->setStyleSheet(wrong_data_edit_);
        return;
    }

    ui->zipCodeEdit->setStyleSheet("");
    ok[4] = true;
}


void EditPersonalDataForm::checkCity() {
    city_ = ui->cityEdit->text();

    if (city_ == "" || city_[0].isDigit() || city_[0].isLower()) {
        ok[5] = false;
        ui->cityEdit->setStyleSheet(wrong_data_edit_);
        return;
    }
    else
        for (auto it = city_.begin() + 1; it != city_.end(); ++it)
            if (it->isDigit()) {
                ok[5] = false;
                ui->cityEdit->setStyleSheet(wrong_data_edit_);
                return;
            }

    ui->cityEdit->setStyleSheet("");
    ok[5] = true;
}


void EditPersonalDataForm::checkAddress() {
    address_ = ui->addressEdit->text();

    if (address_ == "") {
        ok[6] = false;
        ui->addressEdit->setStyleSheet(wrong_data_edit_);
        return;
    }

    ui->addressEdit->setStyleSheet("");
    ok[6] = true;
}


void EditPersonalDataForm::confirmButtonClicked() {
    if (!validate()) {
        ui->errorLabel->setHidden(false);
        return;
    }
    user_->setName(name_);
    user_->setSurname(surname_);
    user_->setEmail(email_);
    user_->setPasswd(passwd_);
    user_->setProvince(province_);
    user_->setP_code(zip_code_);
    user_->setCity(city_);
    user_->setAddress(address_);

    emit editUsersData();

    QMessageBox::about(this, "Info", "Dane zostały zmienione.");

    this->close();
}

bool EditPersonalDataForm::validate() {
    province_ = ui->provincesComboBox->currentText();

    for (int i = 0; i < 7; ++i)
        if (!ok[i])
            return false;
    return true;
}
