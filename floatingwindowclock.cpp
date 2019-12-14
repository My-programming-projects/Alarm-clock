#include "floatingwindowclock.h"
#include "ui_floatingwindowclock.h"


FloatingWindowClock::FloatingWindowClock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FloatingWindowClock),
    clockVisible{false}
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    setContextMenuPolicy(Qt::CustomContextMenu);
    init();
}

FloatingWindowClock::~FloatingWindowClock()
{
    delete ui;
}

void FloatingWindowClock::init()
{
    initFont();
    initTimer();
    initConnections();
}

void FloatingWindowClock::initFont()
{
    setGeometry(10, 10, 180, 100);

    int fontId = QFontDatabase::addApplicationFont(R"(D:\Documents\Alarm_clock\fonts\digital-7\digital-7.ttf)");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(family, 19);

    ui->hourLabel->setFont(font);
}

void FloatingWindowClock::initTimer()
{
    timer.setInterval(1000);
    timer.start();
}

void FloatingWindowClock::initConnections()
{
    QObject::connect(&timer, &QTimer::timeout, this, &FloatingWindowClock::updateDateTime);
    QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(actions(QPoint)));
}

void FloatingWindowClock::updateDateTime()
{
    ui->hourLabel->setText(QDateTime::currentDateTime().toString("HH:mm:ss"));
    ui->hourLabel->setAlignment(Qt::AlignCenter);
    ui->dayLabel->setText(QDateTime::currentDateTime().toString("dddd"));
    ui->dayLabel->setAlignment(Qt::AlignCenter);
    ui->dateLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    ui->dateLabel->setAlignment(Qt::AlignCenter);
}

void FloatingWindowClock::actions(QPoint point)
{
    QAction* actionClose = new QAction("Close");

    QObject::connect(actionClose, &QAction::triggered, this, &FloatingWindowClock::setStateToClose);
    QMenu* menu = new QMenu(this);
    menu->addAction(actionClose);
    menu->exec(point);
}

void FloatingWindowClock::setStateToClose()
{
    emit toClose(true);
    clockVisible = false;
}

void FloatingWindowClock::setVisibleState(bool visible)
{
    clockVisible = visible;
}

bool FloatingWindowClock::isClockVisible() const
{
    return clockVisible;
}
