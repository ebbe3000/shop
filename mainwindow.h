#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loginwithregister.h"
#include "accoutpage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void userButtonClicked();

    void onUserLoggedIn(User* user);

    void logOut();

    void showShoppingCart();

    void showAccount();

private:
    Ui::MainWindow *ui;
    Database db_;
    User* user_;
    AccoutPage* account_page;


    void disableAndHideButton(QPushButton* button);
    void enableAndShowButton(QPushButton* button);
    void guestUiSetup();
    void userUiSetup();
    void productsButtonClicked();

private slots:

};
#endif // MAINWINDOW_H
