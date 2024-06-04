#ifndef FOCUSWATCHER_H
#define FOCUSWATCHER_H

#include <QObject>
#include <QEvent>

class FocusWatcher : public QObject
{
    Q_OBJECT
public:
    explicit FocusWatcher(QObject *parent = nullptr);

    virtual bool eventFilter(QObject *obj, QEvent* event) override;

Q_SIGNALS:
    void focusChanged();
};

#endif // FOCUSWATCHER_H
