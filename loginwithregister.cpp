#include "loginwithregister.h"
#include "ui_loginwithregister.h"

#include <QDebug>

LogInWithRegister::LogInWithRegister(QWidget *parent, Database* db)
    : ui(new Ui::LogInWithRegister)
    , db_(db)
{
    ui->setupUi(this);
    ui->regerrorLabel->setHidden(true);
    ui->logerrLabel->setHidden(true);
    setAttribute(Qt::WA_DeleteOnClose);

    setModal(true);

    ui->stackedWidget->setCurrentIndex(0);
    QObject::connect(ui->loginButton, &QPushButton::clicked,
                     this, &LogInWithRegister::logIn);
    QObject::connect(ui->registerButton, &QPushButton::clicked,
                     this, &LogInWithRegister::registerFun);

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
    qDebug() << "Got into register fun";
    ui->regerrorLabel->setHidden(true);
    if (ui->stackedWidget->currentIndex() == 0) {
        ui->stackedWidget->setCurrentIndex(1);
        return;
    }
    ui->regnameLineEdit->setStyleSheet("");
    ui->regsurnameLineEdit->setStyleSheet("");
    ui->regemailLineEdit->setStyleSheet("");
    ui->regpasswdLineEdit->setStyleSheet("");
    ui->regcityLineEdit->setStyleSheet("");
    ui->regaddressLineEdit->setStyleSheet("");
    ui->regzipcodeLineEdit->setStyleSheet("");


    User user;

    if (!registerValidateData(user))
        return;

    qDebug() << "Valid data inserted";

    if (db_->isEmailInDb(user)) {
        ui->regaddressLabel->setStyleSheet("background-color: red;");
        ui->regaddressLabel->setText("Podany użytkownik już istnieje");
        ui->regerrorLabel->setHidden(false);
        return;
    }

    qDebug() << "User is not in database";

    db_->addUserToDatabase(user);

    qDebug() << "User added to database";

    ui->regerrorLabel->setText("Konto zostało utworzone.");
    ui->regerrorLabel->setStyleSheet("background-color: green;");
    ui->regerrorLabel->setHidden(false);

    qDebug() << "End of register";
}


bool LogInWithRegister::registerValidateData(User& user) {
    bool ok = true;

    QString wrong_data_edit = "background-color: red;";

    //*****************//
    // Name
    //*****************//
    user.setName(ui->regnameLineEdit->text());
    ui->regnameLineEdit->clear();

    if (user.getName() == "" || user.getName()[0].isDigit() || user.getName()[0].isLower()) {
        ok = false;
        ui->regnameLineEdit->setStyleSheet(wrong_data_edit);
    }
    else
        for (auto it = user.getName().begin() + 1; it != user.getName().end(); ++it)
            if (it->isUpper() || it->isDigit()) {
                ok = false;
                ui->regnameLineEdit->setStyleSheet(wrong_data_edit);
            }


    //*****************//
    //Surname
    //*****************//
    user.setSurname(ui->regsurnameLineEdit->text());
    ui->regsurnameLineEdit->clear();

    if (user.getSurname() == "" || user.getSurname()[0].isDigit() || user.getSurname()[0].isLower()) {
        ok = false;
        ui->regsurnameLineEdit->setStyleSheet(wrong_data_edit);
    }
    else
        for (auto it = user.getSurname().begin() + 1; it != user.getSurname().end(); ++it)
            if (it->isUpper() || it->isDigit()) {
                ok = false;
                ui->regsurnameLineEdit->setStyleSheet(wrong_data_edit);
            }

    //*****************//
    // Email
    //*****************//
    user.setEmail(ui->regemailLineEdit->text());
    ui->regemailLineEdit->clear();

    if (user.getEmail() == "" || !user.getEmail().contains("@", Qt::CaseInsensitive) || user.getEmail().size() < 3) {
        ok = false;
        ui->regemailLineEdit->setStyleSheet(wrong_data_edit);
    }


    //*****************//
    //Password
    //*****************//
    user.setPasswd(ui->regpasswdLineEdit->text());
    ui->regpasswdLineEdit->clear();

    if (user.getPasswd() == "" || user.getPasswd().size() < 5) {
        ok = false;
        ui->regpasswdLineEdit->setStyleSheet(wrong_data_edit);
    }


    //*****************//
    // Province
    //*****************//
    user.setProvince(ui->regprovinceComboBox->currentText());
    ui->regprovinceComboBox->setCurrentIndex(0);


    //*****************//
    // Postal code
    //*****************//
    user.setP_code(ui->regzipcodeLineEdit->text());
    ui->regzipcodeLineEdit->clear();

    if (user.getP_code().size() < 6) {
        ok = false;
        ui->regzipcodeLineEdit->setStyleSheet(wrong_data_edit);
    }


    //*****************//
    // City
    //*****************//
    user.setCity(ui->regcityLineEdit->text());
    ui->regcityLineEdit->clear();


    if (user.getCity() == "" || user.getCity()[0].isDigit() || user.getCity()[0].isLower()) {
        ok = false;
        ui->regcityLineEdit->setStyleSheet(wrong_data_edit);
    }
    else
        for (auto it = user.getCity().begin() + 1; it != user.getCity().end(); ++it)
            if (it->isDigit()) {
                ok = false;
                ui->regcityLineEdit->setStyleSheet(wrong_data_edit);
            }


    //*****************//
    // Address
    //*****************//
    user.setAddress(ui->regaddressLineEdit->text());
    ui->regaddressLineEdit->clear();

    if (user.getAddress() == "") {
        ok = false;
        ui->regaddressLineEdit->setStyleSheet(wrong_data_edit);
    }

    return ok;
}
