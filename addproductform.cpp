#include "addproductform.h"
#include "ui_addproductform.h"



AddProductForm::AddProductForm(QWidget *parent, Database* db, User* user)
    : ui(new Ui::AddProductForm)
    , db_(db)
    , user_(user)
{
    ui->setupUi(this);
    ui->photoErrorLabel->setHidden(true);
    ui->emptyError->setHidden(true);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(true);


    QObject::connect(ui->addPhotosButton, &QPushButton::clicked, this, &AddProductForm::addPhotos);
    QObject::connect(ui->addProductButton, &QPushButton::clicked, this, &AddProductForm::addProduct);

}


AddProductForm::~AddProductForm()
{
    delete ui;
}


void AddProductForm::addPhotos() {
    int tmp_max = 5 - pics_.size();
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Otwórz obraz",
                                                          QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                          "Images (*.png *.jpg)");

    if (filenames.isEmpty())
        return;

    if (filenames.size() > tmp_max) {
        ui->photoErrorLabel->setHidden(true);
        return;
    }

    for (auto it : filenames)
        pics_.push_back(QPixmap(it));
}

void AddProductForm::addProduct() {
    if (ui->productNameEdit->text() == "" || ui->productPriceEdit->text() == "." || ui->productAmountEdit->text() == ""
        || ui->productAmountEdit->text().toInt() == 0) {
        ui->emptyError->setHidden(false);
        return;
    }

    Product product(ui->productNameEdit->text(), user_->getId(), ui->productPriceEdit->text().toDouble(),
                    ui->productAmountEdit->text().toInt(), ui->productDescriptionEdit->toPlainText());


    QVector<int> categories(getCheckboxes());

    int id_p = db_->addProductToDatabase(product);

    if (!categories.isEmpty())
        for (auto it : categories)
            db_->addCategorizedProduct(id_p, it);

    QVector<QString> paths;

    if (pics_.isEmpty())
        paths.push_back("D:/shop/shop/imgs/q_mark.png");
    else
        for (auto it : pics_) {
            QTemporaryFile file("D:/shop/shop/imgs/XXXXXX.png");
            file.open();
            it.save(&file, "PNG");
            file.setAutoRemove(false);
            paths.push_back(file.fileName());
        }

    for (auto it : paths)
        db_->addPathToProductToDatabase(id_p, it);
}

QVector<int> AddProductForm::getCheckboxes() {
    QVector<int> result;

    if (ui->electronicBox->isChecked())
        result.push_back(1);
    if (ui->fashionBox->isChecked())
        result.push_back(2);
    if (ui->houseAndGardenBox->isChecked())
        result.push_back(3);
    if (ui->beautyBox->isChecked())
        result.push_back(4);
    if (ui->sportBox->isChecked())
        result.push_back(5);
    if (ui->automotiveBox->isChecked())
        result.push_back(6);
    if (ui->supermarketBox->isChecked())
        result.push_back(7);
    if (ui->healthcareBox->isChecked())
        result.push_back(8);
    if (ui->artBox->isChecked())
        result.push_back(9);

    return result;
}
