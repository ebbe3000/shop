#ifndef LOGINWITHREGISTER_H
#define LOGINWITHREGISTER_H

#include <QDialog>

#include "database.h"


namespace Ui {
class LogInWithRegister;
}

class LogInWithRegister : public QDialog
{
    Q_OBJECT

public:
    explicit LogInWithRegister(QWidget *parent = nullptr, Database* db = nullptr);
    ~LogInWithRegister();

private:
    Ui::LogInWithRegister *ui;
    Database* db_;

    bool registerValidateData(User& user);

public slots:
    void logIn();

    void registerFun();

signals:
    void userLoggedIn(User* user);

};

#endif // LOGINWITHREGISTER_H
