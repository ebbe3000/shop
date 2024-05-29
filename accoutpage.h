#ifndef ACCOUTPAGE_H
#define ACCOUTPAGE_H

#include <QWidget>

#include "addproductform.h"
#include "productlistelement.h"

namespace Ui {
class AccoutPage;
}

class AccoutPage : public QWidget
{
    Q_OBJECT

public:
    explicit AccoutPage(QWidget *parent = nullptr, Database* db = nullptr, User* user = nullptr);
    ~AccoutPage();

    void initializeList();

    void fillUserData();

private:
    Ui::AccoutPage *ui;

    Database* db_;

    User* user_;



private slots:

    void addNewItem();

signals:
    void forwardDeleteProduct(const int id_p, const int amount, const int max_amount);
};

#endif // ACCOUTPAGE_H
