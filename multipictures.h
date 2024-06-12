#ifndef MULTIPICTURES_H
#define MULTIPICTURES_H

#include <QWidget>
#include <QStackedLayout>
#include <QLabel>


namespace Ui {
class MultiPictures;
}

/// Class to display up to 5 pictures in one place
class MultiPictures : public QWidget
{
    Q_OBJECT

public:

    /// Constructor
    ///
    /// @param parent pointer to QWidget, defaul nullptr
    /// @param img vector of QString, default QVector<QString>()
    explicit MultiPictures(QWidget *parent = nullptr, QVector<QString> imgs = QVector<QString>());
    ~MultiPictures();

private:
    Ui::MultiPictures *ui;
    QStackedLayout* stackedLayout;
    int max_size_;
    int curr_page_;

    /// Method adjusts object size to current size of displayed image
    ///
    /// @return void
    void adjustSize();

private slots:

    /// Slot switches to previous image if available
    ///
    /// @return void
    void prevButtonClicked();

    /// Slot switches to next image if available
    ///
    /// @return void
    void nextButtonClicked();
};

#endif // MULTIPICTURES_H
