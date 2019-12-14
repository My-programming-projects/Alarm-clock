#ifndef ALARMSCOLLECTION_H
#define ALARMSCOLLECTION_H

#include <QVector>
#include <memory>

#include "alarm.h"
#include "week.h"
#include "file.h"
#include "deserialization.h"

class AlarmsCollection
{
public:

    AlarmsCollection();

    static void addAlarm(Alarm alarm);
    static void removeAlarm(int index);
    static void clear();
    static void replaceAlarm(int index, const Alarm& alarm);
    static void setEnabled(int index, bool enable);
    static QVector<Alarm> getAlarms();
    static bool isEnabled(int index);
    static bool isEmpty();
    static Alarm getAlarm(int index);
    static void load(const QString& fileName);
    static void save(const QString& fileName);

private:

    static QVector<Alarm> alarms;
};

//////////////////////////////////////////

inline void setAlarmEnabled(int index)
{
    bool enabled = ( AlarmsCollection::isEnabled(index) ? false : true );
    AlarmsCollection::setEnabled(index, enabled);
}

#endif // ALARMSCOLLECTION_H
