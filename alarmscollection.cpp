#include "alarmscollection.h"

QVector<Alarm> AlarmsCollection::alarms;
//bool AlarmsCollection::isAlarmFound;
//int AlarmsCollection::alarmToTriggered;

//int AlarmsSearcher::numberOfActiveAlarm;
//bool AlarmsSearcher::isAlarmFound;

AlarmsCollection::AlarmsCollection()  { }

void AlarmsCollection::addAlarm(Alarm alarm)
{
    alarms.push_back(alarm);
}

void AlarmsCollection::removeAlarm(int index)
{
    alarms.remove(index);
}

void AlarmsCollection::clear()
{
    alarms.clear();
}

void AlarmsCollection::replaceAlarm(int index, const Alarm &alarm)
{
    alarms[index] = alarm;
}

void AlarmsCollection::setEnabled(int index, bool enable)
{
    alarms[index].setEnabled(enable);
}

QVector<Alarm> AlarmsCollection::getAlarms()
{
    return alarms;
}

/*Alarm AlarmsCollection::getAlarmToTriggered()
{
    return alarms[alarmToTriggered];
}

bool AlarmsCollection::isDayFound(Alarm alarm)
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

void AlarmsCollection::checkAlarmTimes(const QTime& time)
{
    for(int i = 0; i < alarms.size(); ++i)
    {
        if( (alarms[i].getTime() == time) && (alarms[i].isEnabled()) &&
            (isDayFound(alarms[i])) )
        {
            isAlarmFound = true;
            alarmToTriggered = i;
            break;
        }
    }
}*/

bool AlarmsCollection::isEnabled(int index)
{
    return alarms[index].isEnabled();
}

/*bool AlarmsCollection::isAlarm()
{
    return isAlarmFound;
}*/

bool AlarmsCollection::isEmpty()
{
    return alarms.empty();
}

/*void AlarmsCollection::reset()
{
    alarms[alarmToTriggered].setEnabled(false);
    isAlarmFound = false;
}*/

Alarm AlarmsCollection::getAlarm(int index)
{
    return alarms[index];
}

void AlarmsCollection::load(const QString &fileName)
{
    File file(fileName, QIODevice::ReadOnly);

    QStringList data = file.load();

    clear();

    for(int i = 0; i < data.size(); ++i)
    {
        Deserialization deserialization(data[i]);
        Alarm alarm = deserialization.getAlarm();
        addAlarm(alarm);
    }
}

void AlarmsCollection::save(const QString &fileName)
{
    File file(fileName, QIODevice::WriteOnly);

    for(int i = 0; i < alarms.size(); ++i)
    {
        file.saveAlarmSettings(alarms[i].isEnabled(), alarms[i].getTime().hour(), alarms[i].getTime().minute(), alarms[i].getDays(), alarms[i].getNote());
        file.saveSnoozeSettings(alarms[i].getSnooze().isEnabled(), alarms[i].getSnooze().getDuration());

        SoundSettings soundsSettings = alarms[i].getSoundSettings();
        file.saveSoundsSettings(soundsSettings.getNotConvertedVolume(), soundsSettings.getFileNumber(), soundsSettings.getDuration(), soundsSettings.getName());
    }
}
