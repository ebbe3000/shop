#ifndef LOGINWITHREGISTER_H
#define LOGINWITHREGISTER_H

#include <QDialog>
#include <QMessageBox>

#include "database.h"
#include "focuswatcher.h"


namespace Ui {
class LogInWithRegister;
}

/// Form which lets user to log in or register
class LogInWithRegister : public QDialog
{
    Q_OBJECT

public:

    /// Constructor
    ///
    /// @param db pointer to database
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

    /// Method validates all field, if no objections returns true, else false.
    ///
    /// @return bool
    bool registerValidateData();

public slots:
    /// Method to log in
    ///
    /// If current page is register, function changes page to log in.
    /// Else validates data and if correct logs user in.
    /// @return void
    void logIn();

    /// Method to register
    ///
    /// If current page is log in, function changes page to register.
    /// Else validates data and if correct creates user in database.
    /// @return void
    void registerFun();

signals:

    /// Signal emited on successfull log in.
    void userLoggedIn(User* user);

private slots:

    /// Slot checks if inserted name is acceptable
    ///
    /// @return void
    void checkName();

    /// Slot checks if inserted surname is acceptable
    ///
    /// @return void
    void checkSurname();

    /// Slot checks if inserted email is acceptable
    ///
    /// @return void
    void checkEmail();

    /// Slot checks if inserted password is acceptable
    ///
    /// @return void
    void checkPasswd();

    /// Slot checks if inserted zip code is acceptable
    ///
    /// @return void
    void checkZipCode();

    /// Slot checks if inserted city is acceptable
    ///
    /// @return void
    void checkCity();

    /// Slot checks if inserted address is acceptable
    ///
    /// @return void
    void checkAddress();

};

#endif // LOGINWITHREGISTER_H
