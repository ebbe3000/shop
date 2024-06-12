#ifndef EDITPERSONALDATAFORM_H
#define EDITPERSONALDATAFORM_H

#include <QDialog>
#include <QMessageBox>

#include "user.h"
#include "focuswatcher.h"

namespace Ui {
class EditPersonalDataForm;
}

/// Form in which user can change its' data
class EditPersonalDataForm : public QDialog
{
    Q_OBJECT

public:
    /// Constructor
    ///
    /// @param user pointer to User object
    explicit EditPersonalDataForm(User* user);
    ~EditPersonalDataForm();

private:
    Ui::EditPersonalDataForm *ui;
    User* user_;
    QString name_;
    QString surname_;
    QString email_;
    QString passwd_;
    QString province_;
    QString zip_code_;
    QString city_;
    QString address_;
    QString wrong_data_edit_;
    bool ok[7];

    /// Method checks if data in form is validated
    ///
    /// @return bool
    bool validate();

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

    /// Slot checks if password name is acceptable
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

    /// Slot which activates when confirm buttons is clicked
    ///
    /// Slots uses validate method to check if everything is correct.
    /// If so then emits editUsersData signal, shows Message and closes window
    void confirmButtonClicked();

signals:

    /// Signal which is emited when users successfully changes data
    ///
    /// @return void
    void editUsersData();

};

#endif // EDITPERSONALDATAFORM_H
