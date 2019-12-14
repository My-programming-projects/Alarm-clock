#include "table.h"
#include "ui_table.h"



Table::Table(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Table),
    checkBoxNumber{},
    clickedRow{},
    rightClickedRow{}
{
    ui->setupUi(this);

    QObject::connect(ui->tableOfAlarms, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(setDoubleClickedRow(int, int)));
    QObject::connect(ui->tableOfAlarms, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(editAlarm(QPoint)));

    ui->tableOfAlarms->verticalHeader()->setVisible(false);
}

Table::~Table()
{
    delete ui;
}

void Table::addAlarm(Alarm alarm)
{
    auto rowCount = ui->tableOfAlarms->rowCount();
    ui->tableOfAlarms->setRowCount(rowCount + 1);
    setTableContents(rowCount, alarm);
}

void Table::updateStyleSheet(const QString& styleSheet)
{
    ui->tableOfAlarms->setStyleSheet(styleSheet);

    for(int i = 0; i < ui->tableOfAlarms->rowCount(); ++i)
    {
        QWidget* widget = ui->tableOfAlarms->cellWidget(i, Column::Enabled);
        QCheckBox* checkBox = widget->findChild<QCheckBox*>();

        if(checkBox)
        {
            checkBox->setStyleSheet(styleSheet);
        }
    }
}

void Table::clone()
{
    if(clickedRow >= 0)
    {
        auto alarm = AlarmsCollection::getAlarm(clickedRow);
        addAlarm(alarm);
        AlarmsCollection::addAlarm(alarm);
    }
}

void Table::clear()
{
    ui->tableOfAlarms->clear();
    ui->tableOfAlarms->setRowCount(0);
}

void Table::updateTable(Alarm alarm)
{
    setTableContents(clickedRow, alarm);
}

void Table::setTableContents(int row, Alarm alarm)
{
    setCheckBox(row, alarm.isEnabled());
    setItem(row, Column::Hour, alarm.getTime().toString("HH:mm"));
    setDays(row, alarm.getDays());
    setItem(row, Column::SoundName, alarm.getSoundSettings().getName());
    setItem(row, Column::Note, alarm.getNote());
}

void Table::removeAlarm()
{
    auto selectedRows = ui->tableOfAlarms->selectionModel()->selectedRows();

    for(auto current : selectedRows)
    {
        AlarmsCollection::removeAlarm(current.row());
        ui->tableOfAlarms->removeRow(current.row());
    }
}

void Table::setCheckBox(int row, bool isChecked)
{
    QWidget* checkBoxWidget = new QWidget(this);
    QCheckBox* checkBox = new QCheckBox(this);
    setCheckBoxInLayout(checkBoxWidget, checkBox, isChecked);

    QObject::connect(checkBox, &QCheckBox::stateChanged, [row]{ setAlarmEnabled(row); } );
    ui->tableOfAlarms->setCellWidget(row, Column::Enabled, checkBoxWidget);
}

void Table::setDays(int row, const QVector<int> daysNumbers)
{
    QString daysNames = writeDays(daysNumbers);
    setItem(row, Column::Days, daysNames);
}

void Table::setItem(int row, Column column, const QString& text)
{
    QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(text);
    tableWidgetItem->setTextAlignment(Qt::AlignCenter);
    tableWidgetItem->setFlags(tableWidgetItem->flags() ^ Qt::ItemIsEditable);

    ui->tableOfAlarms->setItem(row, column, tableWidgetItem);
    ui->tableOfAlarms->setContextMenuPolicy(Qt::CustomContextMenu);
}

int Table::getCheckBoxNumber() const
{
    return checkBoxNumber;
}

QVector<int> Table::getSelected()
{
    QVector<int> selected = findCheckedAlarms(ui->tableOfAlarms);

    return selected;
}

int Table::getClickedRow() const noexcept
{
    return clickedRow;
}

void Table::setCheckBoxNumber(int number)
{
    bool enabled = ( AlarmsCollection::isEnabled(number) ? false : true );
    AlarmsCollection::setEnabled(number, enabled);
}

void Table::setDoubleClickedRow(int row, int col)
{
    clickedRow = row;
    auto alarm = AlarmsCollection::getAlarm(clickedRow);
    openAlarmCreator(this, this, true);
}

void Table::toRemove()
{
    removeAlarm();
}

void Table::editAlarm(QPoint point)
{    
    TableActionMenu* menu = new TableActionMenu(this);

    menu->popup(ui->tableOfAlarms->viewport()->mapToGlobal(point));

    QObject::connect(menu, &TableActionMenu::removeAlarm, this, &Table::toRemove);
    QObject::connect(menu, &TableActionMenu::editAlarm, [this]{ openAlarmCreator(this, this, true); });
    QObject::connect(menu, &TableActionMenu::cloneAlarm, this, &Table::clone);
}

