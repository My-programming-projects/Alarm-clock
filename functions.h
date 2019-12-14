#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QCheckBox>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include "alarmscollection.h"
#include "duration.h"
#include <functional>


inline QVector<QCheckBox*> createCheckBoxVector(const QStringList& texts)
{
    QVector<QCheckBox*> checkBoxes;

    std::generate_n(std::back_inserter(checkBoxes), texts.size(),
                    [texts, count = 0]()mutable{ return new QCheckBox(texts[count++]) ;});

    return checkBoxes;
}

inline void addCheckBoxesToLayout(const QVector<QCheckBox*>& checkBoxes, QVBoxLayout* layout)
{
    for(int i = 0; i < checkBoxes.size(); ++i)
    {
        layout->addWidget(checkBoxes[i]);
    }
}

inline void updateActionsChecktable(int index, QList<QAction*> actions)
{
    for(int i = 0; i < actions.size(); ++i)
    {
        bool checktable = i == index ? true : false;

        actions[i]->setCheckable(checktable);
        actions[i]->setChecked(checktable);
    }
}

inline void setActionsEnabled(QAction* removeAction, QAction* editAction, QAction* cloneAction)
{
    bool enabled = !(AlarmsCollection::isEmpty());

    removeAction->setEnabled(enabled);
    editAction->setEnabled(enabled);
    cloneAction->setEnabled(enabled);
}

#endif // FUNCTIONS_H
