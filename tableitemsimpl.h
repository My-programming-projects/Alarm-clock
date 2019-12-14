#ifndef TABLEITEMSIMPL_H
#define TABLEITEMSIMPL_H

#include <QCheckBox>
#include <QHBoxLayout>
#include <QTableWidget>

#include "alarmscollection.h"

inline QString writeDays(const QVector<int>& days)
{
    QString daysStr;

    if(days.size() == 7)
    {
        daysStr = "Daily";
    }
    else
    {
        for(int i = 0; i < days.size(); ++i)
        {
            auto dayName = Week::getDay(days[i]);
            QString inSpace = ( i == days.size() - 1 ? "." : ", " );
            daysStr += dayName + inSpace;
        }
    }

    return daysStr;
}

inline void setCheckBoxInLayout(QWidget* widget, QCheckBox* checkBox, bool checked)
{
    checkBox->setChecked(checked);

    QHBoxLayout* layoutCheckBox = new QHBoxLayout(widget);
    layoutCheckBox->addWidget(checkBox);
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(0, 0, 0, 0);
}

inline QVector<int> findCheckedAlarms(QTableWidget* table)
{
    QVector<int> selected;

    for(int i = 0; i < table->rowCount(); ++i)
    {
        auto item = table->item(i, 0);

        if(item->isSelected())
        {
            selected.push_back(i);
        }
    }

    return selected;
}

#endif // TABLEITEMSIMPL_H
