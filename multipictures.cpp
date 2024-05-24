#include "multipictures.h"
#include "ui_multipictures.h"

MultiPictures::MultiPictures(QWidget *parent, const int id_p)
    : QWidget(parent)
    , ui(new Ui::MultiPictures)
{
    ui->setupUi(this);
}

MultiPictures::~MultiPictures()
{
    delete ui;
}
