#ifndef MULTIPICTURES_H
#define MULTIPICTURES_H

#include <QWidget>
#include <QStackedLayout>
#include <QLabel>


namespace Ui {
class MultiPictures;
}

class MultiPictures : public QWidget
{
    Q_OBJECT

public:
    explicit MultiPictures(QWidget *parent = nullptr, QVector<QString> imgs = QVector<QString>());
    ~MultiPictures();

private:
    Ui::MultiPictures *ui;
    QStackedLayout* stackedLayout;
    int max_size_;
    int curr_page_;
    void adjustSize();

private slots:
    void prevButtonClicked();
    void nextButtonClicked();
};

#endif // MULTIPICTURES_H
