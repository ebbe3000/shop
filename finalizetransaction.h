#ifndef FINALIZETRANSACTION_H
#define FINALIZETRANSACTION_H

#include <QWidget>

#include "productlistelement.h"

namespace Ui {
class FinalizeTransaction;
}

/// Form through which user can finalize transaction
class FinalizeTransaction : public QDialog
{
    Q_OBJECT

public:

    /// Contructor
    ///
    /// @param user pointer to user, default nullptr
    /// @param products vector of pointers to products in shopping cart
    /// @param price overall cost of shopping cart
    explicit FinalizeTransaction(const User* user = nullptr, const QVector<Product*>& products = QVector<Product*>(), const double price = 0.0);
    ~FinalizeTransaction();

private:
    Ui::FinalizeTransaction *ui;

private slots:

    /// Slot which activates on Confirm button clicked
    ///
    /// Emits boughtProducts
    void onConfirmButtonClicked();

signals:

    /// Signal which emits string of delivery option
    ///
    /// @param delivery_option QString of delivery option
    void boughtProducts(const QString& delivery_option);

};

#endif // FINALIZETRANSACTION_H
