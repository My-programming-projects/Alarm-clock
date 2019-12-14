#include "deserialization.h"

Deserialization::Deserialization(const QString& reqData) :
    data(reqData)
{
    start();
}

void Deserialization::start()
{
    QStringList splitedData = data.split("|", QString::SkipEmptyParts);

    bool isAlarmEnabled = QVariant(splitedData[AlarmEnabled]).toBool();
    int hour = splitedData[Hour].toInt();
    int minutes = splitedData[Minute].toInt();

    QStringList daysSplited = splitedData[Days].split("", QString::SkipEmptyParts);
    QVector<int> days(daysSplited.size());
    std::transform(daysSplited.begin(), daysSplited.end(), days.begin(), [](QString str){ return str.toInt(); });

    alarm = Alarm(isAlarmEnabled, QTime(hour, minutes), days, splitedData[Note]);

    bool isSnoozeEnabled = QVariant(splitedData[SnoozeEnabled]).toBool();
    int snoozeDuration = splitedData[SnoozeDuration].toInt();

    int soundVolume = splitedData[SoundVolume].toInt();
    int soundFileNumber = splitedData[SoundFileNumber].toInt();
    int soundDuration = splitedData[SoundDuration].toInt();

    Snooze snooze(snoozeDuration, isSnoozeEnabled);
    SoundSettings s(soundVolume, soundFileNumber, soundDuration, splitedData[SoundName]);

    alarm.setSnooze(snooze);
    alarm.setSoundSettings(s);
}

Alarm Deserialization::getAlarm() const
{
    return alarm;
}
