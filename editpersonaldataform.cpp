#include "editpersonaldataform.h"
#include "ui_editpersonaldataform.h"

EditPersonalDataForm::EditPersonalDataForm()
    : ui(new Ui::EditPersonalDataForm)
{
    ui->setupUi(this);
}

EditPersonalDataForm::~EditPersonalDataForm()
{
    delete ui;
}
