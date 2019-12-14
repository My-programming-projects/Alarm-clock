#ifndef ALARMSTABLE_H
#define ALARMSTABLE_H

#include <QDialog>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QPoint>
#include <QMenu>


#include "tableitemsimpl.h"
#include "week.h"
#include "alarmeditor.h"
#include "functions.h"
#include "tableactionmenu.h"


namespace Ui {
class Table;
}

class Table : public QDialog
{
    Q_OBJECT

public:

    explicit Table(QWidget *parent = nullptr);
    ~Table();

    void addAlarm(Alarm alarm);
    void updateTable(Alarm alarm);
    void replaceAlarm(int row, const Alarm& alarm);
    void removeAlarm();
    void clone();
    void clear();
    int getCheckBoxNumber() const;
    int getClickedRow() const noexcept;
    QVector<int> getSelected();

    void updateStyleSheet(const QString& styleSheet);

signals:

    void doubleClick(bool state = false);
    void mouseRightClick(bool state = false);

private slots:

    void setTableContents(int row, Alarm alarm);
    void setDoubleClickedRow(int row, int col);
    void editAlarm(QPoint point);
    void toRemove();

private:

    Ui::Table *ui;

    enum Column
    {
        Enabled,
        Hour,
        Days,
        SoundName,
        Note
    };

    void setCheckBox(int row, bool isChecked);
    void setDays(int row, const QVector<int> daysNumbers);
    void setItem(int row, Column column, const QString& text);

    void setCheckBoxNumber(int number);

    int checkBoxNumber;
    int clickedRow;
    int rightClickedRow;
};


inline void openAlarmCreator(QWidget* parent, Table* alarmsTable, bool onlyEdit)
{
    AlarmEditor* alarmEditor;

    if(onlyEdit)
    {
        Alarm alarm = AlarmsCollection::getAlarm(alarmsTable->getClickedRow());
        alarmEditor = new AlarmEditor(alarm, parent);
    }
    else
    {
        alarmEditor = new AlarmEditor(parent);
    }

    alarmEditor->setModal(true);

    if(alarmEditor->exec() == QDialog::Accepted)
    {
        auto alarm = alarmEditor->getAlarm();

        if(!onlyEdit)
        {
            alarmsTable->addAlarm(alarm);
            AlarmsCollection::addAlarm(alarm);
        }
        else
        {
            alarmsTable->updateTable(alarm);
            AlarmsCollection::replaceAlarm(alarmsTable->getClickedRow(), alarm);
        }
    }
}

#endif // ALARMSTABLE_H
