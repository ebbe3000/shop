#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "accoutpage.h"
#include "shoppingcart.h"

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

    void showAccount();

    void deleteProduct(const int id_p, const int amount, const int max_amount);

private:
    Ui::MainWindow *ui;
    Database db_;
    User* user_;
    AccoutPage* account_page_;
    int page_size_;
    int product_page_index_;
    int records_amount_;
    QVector<int> selected_categories_;
    ShoppingCart* shopping_cart_page_;
    QString search_phrase_;



    void disableAndHideButton(QPushButton* button);
    void enableAndShowButton(QPushButton* button);
    void guestUiSetup();
    void userUiSetup();
    void productsButtonClicked();
    void loadProductList();
    void getSelectedCategories();


private slots:
    void mainNextButtonClicked();
    void mainPrevButtonClicked();
    void categoriesButtonClicked();
    void searchButtonClicked();
    void clearCategoriesButtonsClicked();
    void addProductToShoppingCart(const int id_p, const int amount);
    void onShoppingCartButtonClicked();

};
#endif // MAINWINDOW_H
