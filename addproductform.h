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
    explicit AddProductForm(QWidget *parent = nullptr, Database* db = nullptr, User* user = nullptr);
    ~AddProductForm();

private:
    Ui::AddProductForm *ui;
    Database* db_;
    User* user_;
    QVector<QPixmap> pics_;

    QVector<int> getCheckboxes();

private slots:
    void addPhotos();

    void addProduct();

signals:
    void productAdded();

};

#endif // ADDPRODUCTFORM_H
