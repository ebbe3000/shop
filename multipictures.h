#ifndef MULTIPICTURES_H
#define MULTIPICTURES_H

#include <QWidget>

#include "database.h"

namespace Ui {
class MultiPictures;
}

class MultiPictures : public QWidget
{
    Q_OBJECT

public:
    explicit MultiPictures(QWidget *parent = nullptr, const int id_p);
    ~MultiPictures();

private:
    Ui::MultiPictures *ui;
    QVector<QPixmap> pics_;
};

#endif // MULTIPICTURES_H
