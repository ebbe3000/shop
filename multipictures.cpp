#include "multipictures.h"
#include "ui_multipictures.h"

MultiPictures::MultiPictures(QWidget *parent, QVector<QString> imgs)
    : QWidget(parent)
    , ui(new Ui::MultiPictures)
    , max_size_(imgs.size())
    , curr_page_(0)
{
    ui->setupUi(this);
    stackedLayout = new QStackedLayout;
    ui->verticalLayout->insertLayout(0, stackedLayout);
    stackedLayout->setParent(ui->verticalLayout);


    for (auto it : imgs) {
        QLabel* label = new QLabel(this);
        label->setPixmap(QPixmap(it).scaledToHeight(300));
        label->setAlignment(Qt::AlignCenter);
        stackedLayout->addWidget(label);
    }

    ui->prevButton->setDisabled(true);
    if (max_size_ == 1)
        ui->nextButton->setDisabled(true);

    QObject::connect(ui->prevButton, &QPushButton::clicked, this, &MultiPictures::prevButtonClicked);
    QObject::connect(ui->nextButton, &QPushButton::clicked, this, &MultiPictures::nextButtonClicked);

}


MultiPictures::~MultiPictures()
{
    delete ui;
}

void MultiPictures::adjustSize() {
    for (int i = 0; i < stackedLayout->count (); ++i)
    {
        // determine the vertical size policy
        QSizePolicy::Policy policy = QSizePolicy::Ignored;
        if (i == stackedLayout->currentIndex ())
            policy = QSizePolicy::Expanding;

        // update the size policy
        QWidget* pPage = stackedLayout->widget(i);
        pPage->setSizePolicy (policy, policy);
    }
}


void MultiPictures::prevButtonClicked() {
    stackedLayout->setCurrentIndex(--curr_page_);
    adjustSize();

    if (curr_page_ == 0)
        ui->prevButton->setDisabled(true);

    if (curr_page_ != max_size_ - 1)
        ui->nextButton->setDisabled(false);

}


void MultiPictures::nextButtonClicked() {
    stackedLayout->setCurrentIndex(++curr_page_);
    adjustSize();

    if (curr_page_ == max_size_ - 1)
        ui->nextButton->setDisabled(true);

    if (curr_page_ != 0)
        ui->prevButton->setDisabled(false);
}
