#ifndef ACCOUTPAGE_H
#define ACCOUTPAGE_H

#include <QWidget>

#include "addproductform.h"
#include "productlistelement.h"
#include "editpersonaldataform.h"

namespace Ui {
class AccoutPage;
}

/// This widget contains users' info and its' products for sale
///
/// Available only when user is logged in. From here user can change its personal
/// information, add product, delete them or vary amount
class AccoutPage : public QWidget
{
    Q_OBJECT

public:
    /// Constructor
    ///
    /// @param parent pointer to father widget
    /// @param db pointer to dabase default nullptr
    /// @param user pointer to user, default nullptr
    explicit AccoutPage(QWidget *parent = nullptr, Database* db = nullptr, User* user = nullptr);
    ~AccoutPage();

    /// Method that loads users' products for sale
    ///
    /// @returns void
    void initializeList();

    /// Fills users personal data
    ///
    /// @returns void
    void fillUserData();

private:
    Ui::AccoutPage *ui;

    Database* db_;

    User* user_;



private slots:

    /// Displays form to add new product
    ///
    /// Creates instance of AddProductForm
    /// @returns void
    /// @see AddProductForm
    void addNewItem();

    /// Displays form to edit personal data
    ///
    /// Creates instance of EditPersonalDataForm
    /// @returns void
    /// @see EditPersonalDataForm
    void editPersonalData();

    /// Slot called when user changed its' data successfully
    ///
    /// @returns void
    void editData();

signals:

    /// Signal which is emited when user users decides to delete item
    ///
    /// @returns void
    /// @param id_p products' id
    /// @param amount number of copies of product
    /// @param max_amount number of all copies of product
    void forwardDeleteProduct(const int id_p, const int amount, const int max_amount);
};

#endif // ACCOUTPAGE_H
