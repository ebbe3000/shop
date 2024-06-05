#ifndef EDITPERSONALDATAFORM_H
#define EDITPERSONALDATAFORM_H

#include <QDialog>

#include "user.h"

namespace Ui {
class EditPersonalDataForm;
}

class EditPersonalDataForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditPersonalDataForm(const User* user);
    ~EditPersonalDataForm();

private:
    Ui::EditPersonalDataForm *ui;
};

#endif // EDITPERSONALDATAFORM_H
