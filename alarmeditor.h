#ifndef ALARMEDITOR_H
#define ALARMEDITOR_H

#include <QDialog>
#include <QCheckBox>
#include <QSpinBox>
#include <QSlider>
#include <QComboBox>
#include <QTime>
#include <QDate>
#include <QStringRef>
#include <memory>

#include "week.h"
#include "functions.h"
#include "sounds.h"
#include "alarm.h"
#include "stylessheets.h"

template<typename Widget>
inline void setWidgetEnabled(QCheckBox* checkBox, Widget* widget)
{
    bool enabled = ( checkBox->isChecked() ? true : false );
    widget->setEnabled(enabled);
}

inline int getDuration(QString text)
{
    return Duration::get(text);
}

namespace Ui {
class AlarmEditor;
}

class AlarmEditor : public QDialog
{
    Q_OBJECT

public:

    explicit AlarmEditor(QWidget* parent = nullptr);
    explicit AlarmEditor(const Alarm& alarm, QWidget* parent = nullptr);

    ~AlarmEditor();

    Alarm getAlarm();

private slots:

    void setValueOfProgress();
    void playSound();
    void createAlarm();

private:

    void initialize();
    void initializeWidgetsState();
    void setConnections();
    void setCheckBoxesConnections();
    void buildWidgets();

    QVector<int> getDays();

    Ui::AlarmEditor *ui;

    Alarm alarm;
    QVector<QCheckBox*> daysCheckBoxes;
};

class AlarmCreatorInitializer
{
public:

    enum ComboBoxType
    {
        AlarmComboBox,
        SnoozeComboBox
    };

    AlarmCreatorInitializer(const Alarm& reqAlarm) :
        alarm{reqAlarm} { }

    void initSpinBox(QSpinBox* spinBox1, QSpinBox* spinBox2)
    {
        spinBox1->setValue(alarm.getTime().hour());
        spinBox2->setValue(alarm.getTime().minute());
    }

    void initSlider(QSlider* slider)
    {
        slider->setValue(alarm.getSoundSettings().getNotConvertedVolume());
    }

    void initComboBox(QComboBox* comboBox, ComboBoxType type)
    {
        for(int i = 0; i < comboBox->count(); ++i)
        {
            auto itemText = comboBox->itemText(i);
            auto alarmDuration = ( type == AlarmComboBox ? alarm.getSoundSettings().getDuration() : alarm.getSnooze().getDuration() ) ;
            auto duration = Duration::find(itemText);

            if(alarmDuration == duration.second)
            {
                comboBox->setCurrentIndex(i);
                break;
            }
        }
    }

    void initComboBox(QComboBox* comboBox)
    {
        comboBox->setCurrentIndex(alarm.getSoundSettings().getFileNumber());
    }

    void initCheckBox(QCheckBox* checkBox1, QVector<QCheckBox*> checkBoxes)
    {
        checkBox1->setChecked(alarm.getSnooze().isEnabled());

        for(int i = 0; i < alarm.getDays().size(); ++i)
        {
            checkBoxes[alarm.getDays()[i]]->setChecked(true);
        }
    }

private:

    Alarm alarm;
};

#endif // ALARMCREATOR_H
