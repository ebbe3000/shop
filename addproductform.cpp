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
    QObject::connect(ui->productDescriptionEdit, &QPlainTextEdit::textChanged, this, &AddProductForm::descriptionHandler);

}


AddProductForm::~AddProductForm()
{
    delete ui;
}


void AddProductForm::addPhotos() {
    int tmp_max = 5 - pics_.size();
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Otwórz obraz",
                                                          QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                          "Images (*.png *.jpg *.jpeg)");

    if (filenames.isEmpty())
        return;

    if (filenames.size() > tmp_max) {
        ui->photoErrorLabel->setHidden(false);
        return;
    }

    for (auto it : filenames)
        pics_.push_back(QPair<QPixmap, QString>(QPixmap(it), it));

    while (ui->addedPhotosLayout->count() > 0) {
        QLayoutItem* item = ui->addedPhotosLayout->takeAt(0);
        item->widget()->setParent(nullptr);
        ui->addedPhotosLayout->removeWidget(item->widget());
        delete item->widget();
    }

    for (auto it: pics_) {
        QPushButton* push_button = new QPushButton(QIcon(":/icons_white/x.png"), it.second, this);
        ui->addedPhotosLayout->addWidget(push_button, 0, Qt::AlignLeft);
        QObject::connect(push_button, &QPushButton::clicked, this, &AddProductForm::removePhoto);
    }
}



void AddProductForm::removePhoto() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString button_text = button->text();

    for (QVector<QPair<QPixmap, QString>>::iterator it = pics_.begin(); it != pics_.end(); ++it) {
        if ((*it).second == button_text) {
            pics_.erase(it);
            if (it == pics_.end())
                break;
        }
    }

    button->setParent(nullptr);
    delete button;
}


void AddProductForm::addProduct() {
    if (ui->productNameEdit->text() == "" || ui->productPriceEdit->text() == "." || ui->productAmountEdit->text() == ""
        || ui->productAmountEdit->text().toInt() == 0) {
        ui->emptyError->setHidden(false);
        return;
    }

    QString name = ui->productNameEdit->text();

    int pos = name.indexOf("'");

    if (pos != -1) {
        for (int i = 0; i < name.size(); ++i) {
            if (name[i] == '\'') {
                name.insert(i, '\'');
                ++i;
                if (i == name.size())
                    break;
            }
        }
    }



    Product product(std::move(name), user_->getId(), ui->productPriceEdit->text().toDouble(),
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
            it.first.save(&file, "PNG");
            file.setAutoRemove(false);
            paths.push_back(file.fileName());
        }

    for (auto it : paths)
        db_->addPathToProductToDatabase(id_p, it);

    emit productAdded();

    QMessageBox::about(this, "Info", "Produkt dodany");

    this->close();
}

void AddProductForm::descriptionHandler() {
    while (ui->productDescriptionEdit->toPlainText().length() > 100) {
        ui->productDescriptionEdit->moveCursor(QTextCursor::End);
        ui->productDescriptionEdit->textCursor().deletePreviousChar();
    }
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
