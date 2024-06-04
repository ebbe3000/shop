#ifndef EDITPERSONALDATAFORM_H
#define EDITPERSONALDATAFORM_H

#include <QDialog>

namespace Ui {
class EditPersonalDataForm;
}

class EditPersonalDataForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditPersonalDataForm();
    ~EditPersonalDataForm();

private:
    Ui::EditPersonalDataForm *ui;
};

#endif // EDITPERSONALDATAFORM_H
