#ifndef FOCUSWATCHER_H
#define FOCUSWATCHER_H

#include <QObject>
#include <QEvent>

/// Class to watch when QObject loses focus
class FocusWatcher : public QObject
{
    Q_OBJECT
public:

    /// Constructor
    ///
    /// @param parent pointer to QObject, default nullptr
    explicit FocusWatcher(QObject *parent = nullptr);

    /// Method which emits signal when object loses focus
    ///
    /// @param obj pointer to QObject
    /// @param even pointer to QEvent
    /// @return bool
    virtual bool eventFilter(QObject *obj, QEvent* event) override;

Q_SIGNALS:

    /// Signal emitted when object loses focus
    ///
    /// @return void
    void focusChanged();
};

#endif // FOCUSWATCHER_H
