#include "finalizetransaction.h"
#include "ui_finalizetransaction.h"

FinalizeTransaction::FinalizeTransaction(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FinalizeTransaction)
{
    ui->setupUi(this);
}

FinalizeTransaction::~FinalizeTransaction()
{
    delete ui;
}
