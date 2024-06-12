#ifndef BUTTONHOVERWATCHER_H
#define BUTTONHOVERWATCHER_H

#include <QObject>
#include <QPushButton>
#include <QEvent>

class ButtonHoverWatcher : public QObject
{
    Q_OBJECT
public:
    /// Constructor
    ///
    /// @param parent pointer to parent QObject
    /// @param path_to_idle_icon path to icon which gets displayed when button is not in hover mode
    /// @param path_to_hover_icon path to icon which gets displayed when button is in hover mode
    explicit ButtonHoverWatcher(QObject* parent = Q_NULLPTR, const QString& path_to_idle_icon = "", const QString& path_to_hover_icon = "");

    /// Method which changes buttons icon whenever mouser is hovered over
    ///
    /// When mouse is hovered over it changes QObjects' icon to path_to_hover_icon
    /// When mouse leaves filed of watched QObject icon changes to path_to_idle_icon
    /// @param watched pointer to watched QObject
    /// @param pointer to event which triggers filter
    /// @returns bool
    virtual bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;

private:
    const QString path_to_idle_icon_;
    const QString path_to_hover_icon_;
};

#endif // BUTTONHOVERWATCHER_H
