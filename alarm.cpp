#include "alarm.h"

Alarm::Alarm() { }

Alarm::Alarm(bool state, const QTime& reqTime, const QVector<int> reqDays, const QString& reqNote) :
    enabled{state},
    time{reqTime},
    days{reqDays},
    note{reqNote} { }

void Alarm::setEnabled(bool state)
{
    enabled = state;
}

bool Alarm::isEnabled() const noexcept
{
    return enabled;
}

QTime Alarm::getTime() const noexcept
{
    return time;
}

QVector<int> Alarm::getDays() const noexcept
{
    return days;
}

QString Alarm::getNote() const noexcept
{
    return note;
}

void Alarm::setSoundSettings(const SoundSettings& reqSoundSettings)
{
    soundSettings = reqSoundSettings;
}

SoundSettings Alarm::getSoundSettings() const
{
    return soundSettings;
}

void Alarm::setSnooze(const Snooze& reqSnooze)
{
    snooze = reqSnooze;
}

Snooze Alarm::getSnooze() const
{
    return snooze;
}
