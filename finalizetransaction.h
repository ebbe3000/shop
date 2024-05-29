#ifndef FINALIZETRANSACTION_H
#define FINALIZETRANSACTION_H

#include <QWidget>

namespace Ui {
class FinalizeTransaction;
}

class FinalizeTransaction : public QWidget
{
    Q_OBJECT

public:
    explicit FinalizeTransaction(QWidget *parent = nullptr);
    ~FinalizeTransaction();

private:
    Ui::FinalizeTransaction *ui;
};

#endif // FINALIZETRANSACTION_H
