#ifndef ACTIVEALARM_H
#define ACTIVEALARM_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include <memory>

#include "sounds.h"
#include "alarm.h"

namespace Ui {
class ActiveAlarm;
}

class ActiveAlarm : public QDialog
{
    Q_OBJECT

public:
    explicit ActiveAlarm(const Alarm& reqAlarm, QWidget *parent = nullptr);
    ~ActiveAlarm();

    void alarmStart();

private slots:

    void updateTime();
    void close();

private:
    Ui::ActiveAlarm *ui;

    void setConnections();
    void update();
    bool isAlarmFinish();

    Alarm alarm;

    QTimer timer;
    QTimer snoozeTimer;

    int snoozeTime;
};

#endif // ACTIVEALARM_H
