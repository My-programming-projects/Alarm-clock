#include "activealarmdetector.h"

bool ActiveAlarmDetector::isAlarm_;
int ActiveAlarmDetector::numberOfActiveAlarm_;

void ActiveAlarmDetector::detect(const QTime &time)
{
    auto alarms = AlarmsCollection::getAlarms() ;

    for(int i = 0; i < alarms.size(); ++i)
    {
        if( (alarms[i].getTime() == time) && (alarms[i].isEnabled()) &&
            (isDayFound(alarms[i])) )
        {
            isAlarm_ = true;
            numberOfActiveAlarm_ = i;
            break;
        }
    }
}

bool ActiveAlarmDetector::isAlarm()
{
    return isAlarm_;
}

Alarm ActiveAlarmDetector::getActiveAlarm()
{
    return AlarmsCollection::getAlarm(numberOfActiveAlarm_);
}

void ActiveAlarmDetector::reset()
{
    AlarmsCollection::getAlarm(numberOfActiveAlarm_).setEnabled(false);
    isAlarm_ = false;
}

bool ActiveAlarmDetector::isDayFound(Alarm alarm)
{
    bool dayFound = false;

    foreach (auto dayNumber, alarm.getDays())
    {
        if(QDate::currentDate().dayOfWeek() == dayNumber + 1)
        {
            dayFound = true;
            break;
        }
    }

    return dayFound;
}
