#include "loginwithregister.h"
#include "ui_loginwithregister.h"

#include <QDebug>

LogInWithRegister::LogInWithRegister(Database* db)
    : ui(new Ui::LogInWithRegister)
    , db_(db)
    , wrong_data_edit_("background-color: red;")
{
    ui->setupUi(this);
    ui->regerrorLabel->setHidden(true);
    ui->logerrLabel->setHidden(true);
    setAttribute(Qt::WA_DeleteOnClose);

    for (int i = 0; i < 7; ++i)
        ok[i] = false;

    setModal(true);

    ui->stackedWidget->setCurrentIndex(0);
    QObject::connect(ui->loginButton, &QPushButton::clicked,
                     this, &LogInWithRegister::logIn);
    QObject::connect(ui->registerButton, &QPushButton::clicked,
                     this, &LogInWithRegister::registerFun);

    QObject::connect(new FocusWatcher(ui->regnameLineEdit), &FocusWatcher::focusChanged, this, &LogInWithRegister::checkName);
    QObject::connect(new FocusWatcher(ui->regsurnameLineEdit), &FocusWatcher::focusChanged, this, &LogInWithRegister::checkSurname);
    QObject::connect(new FocusWatcher(ui->regemailLineEdit), &FocusWatcher::focusChanged, this, &LogInWithRegister::checkEmail);
    QObject::connect(new FocusWatcher(ui->regpasswdLineEdit), &FocusWatcher::focusChanged, this, &LogInWithRegister::checkPasswd);
    QObject::connect(new FocusWatcher(ui->regzipcodeLineEdit), &FocusWatcher::focusChanged, this, &LogInWithRegister::checkZipCode);
    QObject::connect(new FocusWatcher(ui->regcityLineEdit), &FocusWatcher::focusChanged, this, &LogInWithRegister::checkCity);
    QObject::connect(new FocusWatcher(ui->regaddressLineEdit), &FocusWatcher::focusChanged, this, &LogInWithRegister::checkAddress);

}


LogInWithRegister::~LogInWithRegister()
{
    delete ui;
}


void LogInWithRegister::logIn() {
    ui->logerrLabel->setHidden(true);
    if (ui->stackedWidget->currentIndex() == 1) {
        ui->stackedWidget->setCurrentIndex(0);
        return;
    }

    QString email = ui->logemailLineEdit->text();
    QString passwd = ui->logpasswdLineEdit->text();
    User* user = nullptr;

    if (!db_->isUserInDb(email, passwd, user)) {
        ui->logerrLabel->setHidden(false);
        return;
    }

    ui->logerrLabel->setStyleSheet("background-color: green;");
    ui->logerrLabel->setText("Logowanie powiodło się");
    ui->logerrLabel->setHidden(false);
    ui->loginButton->setDisabled(true);
    ui->registerButton->setDisabled(true);

    // try to sleep app  for about 3 secs

    emit userLoggedIn(user);

    this->close();
}


void LogInWithRegister::registerFun() {
    ui->regerrorLabel->setHidden(true);
    if (ui->stackedWidget->currentIndex() == 0) {
        ui->stackedWidget->setCurrentIndex(1);
        return;
    }

    if (!registerValidateData())
        return;

    User user(name_, surname_, email_, passwd_, province_, zip_code_,
              city_, address_);


    if (db_->isEmailInDb(user)) {
        ui->regaddressLabel->setStyleSheet("background-color: red;");
        ui->regaddressLabel->setText("Podany użytkownik już istnieje");
        ui->regerrorLabel->setHidden(false);
        return;
    }

    db_->addUserToDatabase(user);


    ui->regerrorLabel->setText("Konto zostało utworzone.");
    ui->regerrorLabel->setStyleSheet("background-color: green;");
    ui->regerrorLabel->setHidden(false);
}


void LogInWithRegister::checkName() {
    name_ = ui->regnameLineEdit->text();

    if (name_ == "" || name_[0].isDigit() || name_[0].isLower()) {
        ok[0] = false;
        ui->regnameLineEdit->setStyleSheet(wrong_data_edit_);
        return;
    }
    else
        for (auto it = name_.begin() + 1; it != name_.end(); ++it)
            if (it->isUpper() || it->isDigit()) {
                ok[0] = false;
                ui->regnameLineEdit->setStyleSheet(wrong_data_edit_);
                return;
            }

    ui->regnameLineEdit->setStyleSheet("");
    ok[0] = true;
}

void LogInWithRegister::checkSurname() {
    surname_ = ui->regsurnameLineEdit->text();

    if (surname_ == "" || surname_[0].isDigit() || surname_[0].isLower()) {
        ok[1] = false;
        ui->regsurnameLineEdit->setStyleSheet(wrong_data_edit_);
        return;
    }
    else
        for (auto it = surname_.begin() + 1; it != surname_.end(); ++it)
            if (it->isUpper() || it->isDigit()) {
                ok[1] = false;
                ui->regsurnameLineEdit->setStyleSheet(wrong_data_edit_);
                return;
            }

    ui->regsurnameLineEdit->setStyleSheet("");
    ok[1] = true;
}


void LogInWithRegister::checkEmail() {
    email_ = ui->regemailLineEdit->text();

    if (email_ == "" || !email_.contains("@", Qt::CaseInsensitive) || email_.size() < 3) {
        ok[2] = false;
        ui->regemailLineEdit->setStyleSheet(wrong_data_edit_);
        return;
    }

    ui->regemailLineEdit->setStyleSheet("");
    ok[2] = true;
}

void LogInWithRegister::checkPasswd() {
    passwd_ = ui->regpasswdLineEdit->text();

    if (passwd_ == "" || passwd_.size() < 5) {
        ok[3] = false;
        ui->regpasswdLineEdit->setStyleSheet(wrong_data_edit_);
        return;
    }

    ui->regpasswdLineEdit->setStyleSheet("");
    ok[3] = true;
}

void LogInWithRegister::checkZipCode() {
    zip_code_ = ui->regzipcodeLineEdit->text();

    if (zip_code_.size() < 6) {
        ok[4] = false;
        ui->regzipcodeLineEdit->setStyleSheet(wrong_data_edit_);
        return;
    }

    ui->regzipcodeLineEdit->setStyleSheet("");
    ok[4] = true;
}

void LogInWithRegister::checkCity() {
    city_ = ui->regcityLineEdit->text();

    if (city_ == "" || city_[0].isDigit() || city_[0].isLower()) {
        ok[5] = false;
        ui->regcityLineEdit->setStyleSheet(wrong_data_edit_);
        return;
    }
    else
        for (auto it = city_.begin() + 1; it != city_.end(); ++it)
            if (it->isDigit()) {
                ok[5] = false;
                ui->regcityLineEdit->setStyleSheet(wrong_data_edit_);
                return;
            }

    ui->regcityLineEdit->setStyleSheet("");
    ok[5] = true;
}

void LogInWithRegister::checkAddress() {
    address_ = ui->regaddressLineEdit->text();

    if (address_ == "") {
        ok[6] = false;
        ui->regaddressLineEdit->setStyleSheet(wrong_data_edit_);
        return;
    }

    ui->regaddressLineEdit->setStyleSheet("");
    ok[6] = true;
}


bool LogInWithRegister::registerValidateData() {
    province_ = ui->regprovinceComboBox->currentText();

    for (int i = 0; i < 7; ++i)
        if (!ok[i])
            return false;
    return true;
}
