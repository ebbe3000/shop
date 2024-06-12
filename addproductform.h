#ifndef ADDPRODUCTFORM_H
#define ADDPRODUCTFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include <QStringList>
#include <QTemporaryFile>
#include <QMessageBox>

#include "database.h"

namespace Ui {
class AddProductForm;
}

class AddProductForm : public QDialog
{
    Q_OBJECT

public:
    /// Constructor
    ///
    /// @param parent pointer to parent widget, default nullptr
    /// @param db pointer to database, default nullptr
    /// @param user pointer to user, default nullptr
    explicit AddProductForm(QWidget *parent = nullptr, Database* db = nullptr, User* user = nullptr);
    ~AddProductForm();

private:
    Ui::AddProductForm *ui;
    Database* db_;
    User* user_;
    QVector<QPair<QPixmap, QString>> pics_;

    /// Method which checks selected categories of product
    ///
    /// @returns QVector<int> ids of categories
    QVector<int> getCheckboxes();

private slots:

    /// Slot to add photos to product
    ///
    /// Slot which let's user send up to 5 photos of product for sale, creates
    /// buttons to remove selected photos
    /// @returns void;
    /// @see removePhoto
    void addPhotos();

    /// Slot which get's called when users want to add product with validated
    /// data
    ///
    /// @returns void
    void addProduct();

    /// Slot which limitates length of description QPlainTextEdit
    ///
    /// @returns void
    void descriptionHandler();


    /// Slot gets called when on of buttons to remove photos gets called
    ///
    /// @returns void
    /// @see addPhotos
    void removePhoto();

signals:

    /// Signal which gets emited when user wants to add correctly filled all products data.
    ///
    /// @returns void
    void productAdded();

};

#endif // ADDPRODUCTFORM_H
