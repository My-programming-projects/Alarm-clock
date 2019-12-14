#ifndef FLOATINGWINDOWCLOCK_H
#define FLOATINGWINDOWCLOCK_H

#include <QDialog>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QFontDatabase>
#include <QAction>
#include <QMenu>

namespace Ui {
class FloatingWindowClock;
}

class FloatingWindowClock : public QDialog
{
    Q_OBJECT

public:
    explicit FloatingWindowClock(QWidget *parent = nullptr);
    ~FloatingWindowClock();

    void setVisibleState(bool visible);
    bool isClockVisible() const;

signals:

    void toClose(bool state);

private slots:

    void updateDateTime();
    void actions(QPoint point);
    void setStateToClose();

private:

    void init();
    void initFont();
    void initTimer();
    void initConnections();

    Ui::FloatingWindowClock *ui;

    QTimer timer;
    QFont font;

    bool clockVisible;
};

#endif // FLOATINGWINDOWCLOCK_H
