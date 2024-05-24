#ifndef ACCOUTPAGE_H
#define ACCOUTPAGE_H

#include <QWidget>

#include "addproductform.h"

namespace Ui {
class AccoutPage;
}

class AccoutPage : public QWidget
{
    Q_OBJECT

public:
    explicit AccoutPage(QWidget *parent = nullptr, Database* db = nullptr, User* user = nullptr);
    ~AccoutPage();


    void fillUserData();

private:
    Ui::AccoutPage *ui;

    Database* db_;

    User* user_;


private slots:

    void addNewItem();
};

#endif // ACCOUTPAGE_H
