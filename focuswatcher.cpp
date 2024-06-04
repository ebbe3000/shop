#include "focuswatcher.h"

FocusWatcher::FocusWatcher(QObject *parent)
    : QObject(parent)
{
    if (parent)
        parent->installEventFilter(this);

}

bool FocusWatcher::eventFilter(QObject *obj, QEvent *event) {
    Q_UNUSED(obj)
    if (event->type() == QEvent::FocusOut)
        emit focusChanged();

    return false;
}


