#include "activealarm.h"
#include "ui_activealarm.h"

ActiveAlarm::ActiveAlarm(const Alarm& reqAlarm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActiveAlarm),
    alarm{reqAlarm},
    snoozeTime{}
{
    ui->setupUi(this);

    ui->noteLabel->setText(alarm.getNote());
    ui->hourLabel->setText(QTime::currentTime().toString("HH:mm:ss"));

    setConnections();
    Sounds::setSettings(alarm.getSoundSettings());

    timer.setInterval(1000);
    timer.start();
    snoozeTimer.setInterval(1000);
}

ActiveAlarm::~ActiveAlarm()
{
    delete ui;
}

void ActiveAlarm::setConnections()
{
    QObject::connect(ui->btnOK, &QPushButton::clicked, this, &ActiveAlarm::close);
    QObject::connect(&timer, &QTimer::timeout, this, &ActiveAlarm::updateTime);
}

void ActiveAlarm::alarmStart()
{
    Sounds::play();

    update();
}

void ActiveAlarm::update()
{
    if(Sounds::isFinished())
    {
        snoozeTime++;
    }

    if(alarm.getSnooze().isFinished(snoozeTime))
    {
        snoozeTime = {};
        Sounds::play();
    }
}

void ActiveAlarm::updateTime()
{
    ui->hourLabel->setText(QTime::currentTime().toString("HH:mm:ss"));
    update();
}

void ActiveAlarm::close()
{
    Sounds::stop();

    emit accept();
}

bool ActiveAlarm::isAlarmFinish()
{
    return Sounds::isFinished();
}
