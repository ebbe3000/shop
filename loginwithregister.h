#ifndef LOGINWITHREGISTER_H
#define LOGINWITHREGISTER_H

#include <QDialog>

#include "database.h"
#include "focuswatcher.h"


namespace Ui {
class LogInWithRegister;
}

class LogInWithRegister : public QDialog
{
    Q_OBJECT

public:
    explicit LogInWithRegister(Database* db);
    ~LogInWithRegister();

private:
    Ui::LogInWithRegister *ui;
    Database* db_;
    QString name_;
    QString surname_;
    QString email_;
    QString passwd_;
    QString province_;
    QString zip_code_;
    QString city_;
    QString address_;
    bool ok[7];
    QString wrong_data_edit_;


    bool registerValidateData();

public slots:
    void logIn();

    void registerFun();

signals:
    void userLoggedIn(User* user);

private slots:
    void checkName();
    void checkSurname();
    void checkEmail();
    void checkPasswd();
    void checkZipCode();
    void checkCity();
    void checkAddress();

};

#endif // LOGINWITHREGISTER_H
