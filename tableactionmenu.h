#ifndef TABLEACTIONMENU_H
#define TABLEACTIONMENU_H

#include <QMenu>

#include "alarmscollection.h"

class TableActionMenu : public QMenu
{
    Q_OBJECT

public:

    TableActionMenu(QWidget* parent = nullptr);

signals:

    void addAlarm(bool state);
    void removeAlarm(bool state);
    bool editAlarm(bool state);
    bool cloneAlarm(bool state);

private slots:

    void actionAddTriggered() ;//{ emit addAlarm(true); }
    void actionRemoveTriggered();// { emit removeAlarm(true); }
    void actionEditTriggered();// { emit editAlarm(true); }
    void actionCloneTriggered();// { emit cloneAlarm(true); }

private:

    void setActionsEnabled();

    QAction* actionAdd;
    QAction* actionRemove;
    QAction* actionEdit;
    QAction* actionClone;
};

#endif // TABLEACTIONMENU_H
