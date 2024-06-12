#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "accoutpage.h"
#include "shoppingcart.h"
#include "buttonhoverwatcher.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/// Main Window gathering all other functionalities.
///
/// Lets customer to log in, get products to shopping cart,
/// browse through items.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// Basic contructor
    ///
    /// @param parent If no parent given, set to nullptr
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /// Slot which called on user button clicked
    ///
    /// If there isn't logged user, this brigns you to LogInWithRegister.
    /// If users has alread logged in, button which call this slot is hidden.
    /// @returns void
    void userButtonClicked();

    /// Slot which is called while user has successfully logged in.
    ///
    /// This slot is called when LogInWithRegister::userLoggedIn signal is called.
    /// This slot set's user and creates AccountPage for users. Also updates
    /// shopping cart. If there was something in cart before log in, it is added
    /// to shopping cart. If user had something in cart before last log out
    /// it is still in cart. Launches userUiSetup, loadProductList
    /// @returns void
    void onUserLoggedIn(User* user);

    /// Slot which is called on user log out.
    ///
    /// This slot is called on Log Out button clicked. Launches guestUiSetup and
    /// pops Message Box about log out.
    /// @returns void
    void logOut();

    /// Slot which is called on user account button clicked.
    ///
    /// @returns void
    void showAccount();

    /// Slot which is called on when user deletes his own items
    ///
    /// If user decide to remove all copies of product delets whole product
    /// @param id_p users id
    /// @param amount amount to delete
    /// @param max_amount number of copies, if it's equal to amount whole product gets deleted
    /// @returns void
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


    /// Method to disable and hide button
    ///
    /// @param pointer to button
    /// @returns void
    void disableAndHideButton(QPushButton* button);

    /// Method to enable and show button
    ///
    /// @param pointer to button
    /// @returns void
    void enableAndShowButton(QPushButton* button);

    /// Method which sets buttons for not logged user
    ///
    /// @returns void
    void guestUiSetup();

    /// Method which sets buttons for logged user
    ///
    /// @returns void
    void userUiSetup();

    /// Method which loads main page and loads items
    ///
    /// @returns void
    void productsButtonClicked();

    /// Method which loads main page products list
    ///
    /// @returns void
    void loadProductList();

    /// Method which gathers selected categories
    ///
    /// @returns void
    void getSelectedCategories();


private slots:
    /// Slot which gets called when button to next products page gest called
    ///
    /// Loads next page of products, depends on page_size_, product_page_index_
    /// and records_amount_
    /// @returns void
    /// @see mainNextButtonClicked
    void mainNextButtonClicked();

    /// Slot which gets called when button to previous products page gest called
    ///
    /// Loads previous page of products, depends on page_size_, product_page_index_
    /// and records_amount_
    /// @returns void
    /// @see mainNextButtonClicked
    void mainPrevButtonClicked();

    /// Slot which gets called to show all checkboxes with categories
    ///
    /// Slot except of checkboxes also contains button reset checked categories
    /// @returns void
    /// @see clearCategoriesButtonsClicked
    void categoriesButtonClicked();

    /// Slot which gets called to filter prodcuts
    ///
    /// Filters prodcuts based on search_phrase_ and selected categories
    /// @returns void
    void searchButtonClicked();

    /// Slot which gets called to clear selected checkboxes
    ///
    /// @see categoriesButtonClicked
    void clearCategoriesButtonsClicked();

    /// When users decides to add product to its shopping cart this slot gets called
    ///
    /// When logged user adds item to its shopping its also added in database
    /// @param id_p products id
    /// @param amount number of copies of prodcut
    /// @returns void
    void addProductToShoppingCart(const int id_p, const int amount);

    /// When shopping cart button clicked shows users shopping cart
    ///
    /// Shows items in shopping cart, from here user can buy selected items
    /// @returns void
    void onShoppingCartButtonClicked();

};
#endif // MAINWINDOW_H
