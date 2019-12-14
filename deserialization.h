#ifndef DESERIALIZATION_H
#define DESERIALIZATION_H

#include <QStringList>
#include <QVariant>

#include "alarm.h"

enum Indexes
{
    AlarmEnabled,
    Hour,
    Minute,
    Days,
    Note,
    SnoozeEnabled,
    SnoozeDuration,
    SoundVolume,
    SoundFileNumber,
    SoundDuration,
    SoundName
};

enum class AlarmSettingsIndexes : int
{
    Enabled,
    Hours,
    Minutes,
    Days,
    Note
};

enum class SnoozeSettingsIndexes : int
{
    Enabled,
    Duration
};

enum class SoundSettingsIndexes : int
{
    Volume,
    FileNumber,
    Duration,
    Name
};

class Deserialization
{
public:
    Deserialization(const QString& reqData);

    Alarm getAlarm() const;

private:

    void start();

    QString data;
    Alarm alarm;
};

#endif // DESERIALIZATION_H
