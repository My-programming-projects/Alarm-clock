#ifndef ACTIVEALARMDETECTOR_H
#define ACTIVEALARMDETECTOR_H

#include <QTime>
#include "alarmscollection.h"

class ActiveAlarmDetector
{
public:

    ActiveAlarmDetector() = default;
    ActiveAlarmDetector(const ActiveAlarmDetector& copy) = delete;
    ActiveAlarmDetector(ActiveAlarmDetector&& move) = delete;

    ActiveAlarmDetector& operator=(const ActiveAlarmDetector& rhs) = delete;
    ActiveAlarmDetector& operator=(ActiveAlarmDetector&& rhs) = delete;

    static void detect(const QTime& time);
    static bool isAlarm();
    static Alarm getActiveAlarm();
    static void reset();

private:

    static bool isDayFound(Alarm alarm);

    static bool isAlarm_;
    static int numberOfActiveAlarm_;
};

#endif // ACTIVEALARMDETECTOR_H
