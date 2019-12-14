#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "table.h"
#include "activealarm.h"
#include "duration.h"
#include "floatingwindowclock.h"
#include "filedialog.h"
#include "activealarmdetector.h"
#include "stylesheeteditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void checkAlarms();
    void setAlarmEnabled();
    void showFloatingWindowClock();
    void openStyleSheetEditor();
    void saveData();
    void loadData();

private:

    void initialize();
    void setConnections();
    void save();
    void saveAs();

    Ui::MainWindow *ui;

    Table* table;
    FloatingWindowClock* windowClock;
    QTimer timer;

    bool firstFileOpen;
};

#endif // MAINWINDOW_H
