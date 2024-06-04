#ifndef FINALIZETRANSACTION_H
#define FINALIZETRANSACTION_H

#include <QWidget>

#include "productlistelement.h"

namespace Ui {
class FinalizeTransaction;
}

class FinalizeTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit FinalizeTransaction(const User* user = nullptr, const QVector<Product*>& products = QVector<Product*>(), const double price = 0.0);
    ~FinalizeTransaction();

private:
    Ui::FinalizeTransaction *ui;

private slots:
    void onConfirmButtonClicked();

signals:
    void boughtProducts(const QString& delivery_option);

};

#endif // FINALIZETRANSACTION_H
