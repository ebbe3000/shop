#include "buttonhoverwatcher.h"

ButtonHoverWatcher::ButtonHoverWatcher(QObject *parent,
                                       const QString& path_to_idle_icon,
                                       const QString& path_to_hover_icon)
    : QObject(parent)
    , path_to_hover_icon_(path_to_hover_icon)
    , path_to_idle_icon_(path_to_idle_icon) {}

bool ButtonHoverWatcher::eventFilter(QObject *watched, QEvent *event) {
    QPushButton* button = qobject_cast<QPushButton*>(watched);
    if (!button)
        return false;
    if (event->type() == QEvent::Enter) {
        button->setIcon(QIcon(path_to_hover_icon_));
        return true;
    }

    if (event->type() == QEvent::Leave) {
        button->setIcon(QIcon(path_to_idle_icon_));
        return true;
    }

    return false;
}
