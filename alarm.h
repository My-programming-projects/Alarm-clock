#ifndef ALARM_H
#define ALARM_H

#include <QTime>
#include <QVector>
#include <QDate>

#include "snooze.h"
#include "sounds.h"


class Alarm
{
public:

    Alarm();
    Alarm(bool state, const QTime& reqTime, const QVector<int> reqDays, const QString& reqNote);

    void setEnabled(bool state);
    bool isEnabled() const noexcept;
    QTime getTime() const noexcept;
    QVector<int> getDays() const noexcept;
    QString getNote() const noexcept;
    void setSaveStateFlag(bool savedState);
    bool isSaved() const;

    void setSoundSettings(const SoundSettings& reqSoundsSettings);
    SoundSettings getSoundSettings() const;
    void setSnooze(const Snooze& reqSnooze);
    Snooze getSnooze() const;

private:

    bool enabled;
    QTime time;
    QVector<int> days;
    QString note;

    SoundSettings soundSettings;
    Snooze snooze;
};

#endif // ALARM_H
