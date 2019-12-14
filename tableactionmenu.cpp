#include "tableactionmenu.h"

TableActionMenu::TableActionMenu(QWidget* parent) :
    QMenu(parent),
    actionAdd(new QAction("Add", this)),
    actionRemove(new QAction("Remove", this)),
    actionEdit(new QAction("Edit", this)),
    actionClone(new QAction("Clone"))
{
    actionAdd->setIcon(QIcon(QIcon("D:\\Documents\\Alarm_clock\\icons\\add.png")));
    actionRemove->setIcon(QIcon("D:\\Documents\\Alarm_clock\\icons\\remove.png"));
    actionEdit->setIcon(QIcon("D:\\Documents\\Alarm_clock\\icons\\edit.png"));
    actionClone->setIcon(QIcon("D:\\Documents\\Alarm_clock\\icons\\clone.png"));

    QObject::connect(actionAdd, &QAction::triggered, this, &TableActionMenu::actionAddTriggered);
    QObject::connect(actionRemove, &QAction::triggered, this, &TableActionMenu::actionRemoveTriggered);
    QObject::connect(actionEdit, &QAction::triggered, this, &TableActionMenu::actionEditTriggered);
    QObject::connect(actionClone, &QAction::triggered, this, &TableActionMenu::actionCloneTriggered);

    setActionsEnabled();

    addAction(actionAdd);
    addAction(actionRemove);
    addSeparator();
    addAction(actionEdit);
    addSeparator();
    addAction(actionClone);
}


void TableActionMenu::setActionsEnabled()
{
    bool enabled = !(AlarmsCollection::isEmpty());

    actionRemove->setEnabled(enabled);
    actionEdit->setEnabled(enabled);
    actionClone->setEnabled(enabled);
}

void TableActionMenu::actionAddTriggered()
{
    emit addAlarm(true);
}

void TableActionMenu::actionRemoveTriggered()
{
    emit removeAlarm(true);
}

void TableActionMenu::actionEditTriggered()
{
    emit editAlarm(true);
}

void TableActionMenu::actionCloneTriggered()
{
    emit cloneAlarm(true);
}
