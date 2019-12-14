#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      table(new Table),
      windowClock(new FloatingWindowClock),
      firstFileOpen(false)
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(table);

    setStyleSheet(StylesSheets::getCurrentStyle());
    initialize();
    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    setActionsEnabled(ui->actionRemove, ui->actionEdit, ui->actionClone_2);
    setActionsEnabled(ui->actionRemove, ui->actionEdit, ui->actionClone_2);
    setConnections();
}

void MainWindow::setConnections()
{
    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::loadData);

    QObject::connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveData);
    QObject::connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveData);
    QObject::connect(ui->actionAdd, &QAction::triggered, [this]{ openAlarmCreator(this, table, false);
                                                                 setActionsEnabled(ui->actionRemove, ui->actionEdit, ui->actionClone_2);
                                                                 FileInfo::setSaveState(FileInfo::SaveStateExp::NotSaved); });
    QObject::connect(ui->actionRemove, &QAction::triggered, [this]{ table->removeAlarm();
                                                                    setActionsEnabled(ui->actionRemove, ui->actionEdit, ui->actionClone_2);
                                                                    FileInfo::setSaveState(FileInfo::SaveStateExp::NotSaved); });
    QObject::connect(ui->actionEdit, &QAction::triggered, [this]{ openAlarmCreator(this, table, true); FileInfo::setSaveState(FileInfo::SaveStateExp::NotSaved); });
    QObject::connect(ui->actionClone_2, &QAction::triggered, [this]{ table->clone(); FileInfo::setSaveState(FileInfo::SaveStateExp::NotSaved); });
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(checkAlarms()));
    QObject::connect(table, &Table::accepted, this, &MainWindow::setAlarmEnabled);
    QObject::connect(ui->actionFloating_window_clock, &QAction::triggered, this, &MainWindow::showFloatingWindowClock);
    QObject::connect(ui->actionBacground_options, &QAction::triggered, this, &MainWindow::openStyleSheetEditor);
    QObject::connect(ui->actionClose, &QAction::triggered, this, &QMainWindow::close);
}

void MainWindow::checkAlarms()
{
    ActiveAlarmDetector::detect(QTime::currentTime());

    if(ActiveAlarmDetector::isAlarm())
    {
        auto alarm = ActiveAlarmDetector::getActiveAlarm();
        ActiveAlarm* activeAlarm = new ActiveAlarm(alarm, this);
        activeAlarm->setModal(true);
        activeAlarm->alarmStart();

        if(activeAlarm->exec() == QDialog::Accepted)
        {
            ActiveAlarmDetector::reset();
        }
    }
}

void MainWindow::setAlarmEnabled()
{
    QMessageBox mb;
    mb.setText(QString::number(table->getCheckBoxNumber()));
}

void MainWindow::showFloatingWindowClock()
{
    QObject::connect(windowClock, &FloatingWindowClock::toClose, [this]{ ui->actionFloating_window_clock->setCheckable(false);
                                                                          ui->actionFloating_window_clock->setChecked(false);
                                                                          windowClock->close();
                                                                          windowClock->setVisibleState(false); });

    if(!windowClock->isClockVisible())
    {
        ui->actionFloating_window_clock->setCheckable(true);
        ui->actionFloating_window_clock->setChecked(true);
        windowClock->show();
        windowClock->setVisibleState(true);
    }
    else if(windowClock->isClockVisible())
    {

        ui->actionFloating_window_clock->setCheckable(false);
        ui->actionFloating_window_clock->setChecked(false);
        windowClock->setVisibleState(false);
        windowClock->close();
    }
}

void MainWindow::openStyleSheetEditor()
{
    StyleSheetEditor* styleSheetEditor = new StyleSheetEditor(this);
    styleSheetEditor->setModal(true);

    if(styleSheetEditor->exec() == QDialog::Accepted)
    {
        setUpdatedStyleSheet(this, ui->menubar, ui->toolBar);
        table->updateStyleSheet(StylesSheets::getCurrentStyle());
    }
}

void MainWindow::saveData()
{
    if( (FileInfo::getSaveStateFromBeg() == FileInfo::SaveStateFromBeg::NotSavedYet) &&
        (FileInfo::getCurrentFile() == " ") )
    {
        saveAs();
    }
    else
    {
        save();
    }

    FileInfo::setSaveStateFromBeg(FileInfo::SaveStateFromBeg::AlreadySaved);
}

void MainWindow::save()
{
    AlarmsCollection::save(FileInfo::getCurrentFile());
    FileInfo::setSaveState(FileInfo::SaveStateExp::Saved);
}

void MainWindow::saveAs()
{
    QString save = QFileDialog::getSaveFileName(this, "Save alarm", "alarm.ac", "alarm files(*.ac)");
    AlarmsCollection::save(save);
    FileInfo::setCurrentFile(save);
}

void MainWindow::loadData()
{
    if( (FileInfo::getSaveState() == FileInfo::SaveStateExp::NotSaved) && firstFileOpen )
    {
        QString text = "The document has been modified.\nDo you want to save?";
        QMessageBox infoMessageBox(QMessageBox::Information, "File not saved", text,
                                   QMessageBox::Save | QMessageBox::Cancel);

        if(int ret = infoMessageBox.exec();  ret == QMessageBox::Save)
        {
            saveData();
        }
    }

    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setNameFilter("Alarms(*.ac)");
    fileDialog.setViewMode(QFileDialog::Detail);

    if(fileDialog.exec() == QDialog::Accepted)
    {
        AlarmsCollection::load(fileDialog.selectedFiles()[0]);

        table->clear();

        for(int i = 0; i < AlarmsCollection::getAlarms().size(); ++i)
        {
            table->addAlarm(AlarmsCollection::getAlarms()[i]);
        }

        FileInfo::setCurrentFile(fileDialog.selectedFiles()[0]);
    }

    FileInfo::setSaveStateFromBeg(FileInfo::SaveStateFromBeg::NotSavedYet);

    if(!firstFileOpen)
    {
        firstFileOpen = true;
    }
}
