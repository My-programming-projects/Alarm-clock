#include "alarmeditor.h"
#include "ui_alarmeditor.h"
#include <QMessageBox>

AlarmEditor::AlarmEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmEditor)
{
    ui->setupUi(this);
    initialize();
}

AlarmEditor::AlarmEditor(const Alarm& alarm, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AlarmEditor)
{
    ui->setupUi(this);

    initialize();

    AlarmCreatorInitializer init(alarm);
    init.initSpinBox(ui->spinBoxHour, ui->spinBoxMinutes);
    init.initSlider(ui->soundVolumeSlider);
    init.initComboBox(ui->playSoundComboBox, AlarmCreatorInitializer::AlarmComboBox);
    init.initComboBox(ui->snoozeComboBox, AlarmCreatorInitializer::SnoozeComboBox);
    init.initComboBox(ui->soundsList);
    init.initCheckBox(ui->snoozeCheckBox, daysCheckBoxes);
    ui->textEditNote->setText(alarm.getNote());

}

AlarmEditor::~AlarmEditor()
{
    delete ui;
}

void AlarmEditor::initialize()
{
    buildWidgets();
    initializeWidgetsState();
    setConnections();
}

void AlarmEditor::initializeWidgetsState()
{
    ui->turnVolumeCheckBox->setChecked(true);
    ui->snoozeCheckBox->setChecked(true);
    ui->soundVolumeSlider->setValue(100);

    setValueOfProgress();
}

void AlarmEditor::buildWidgets()
{
    daysCheckBoxes = createCheckBoxVector(QStringList{"every Monday", "every Tuesday", "every Wednesday",
                                                             "every Thursday", "every Friday", "every Saturday", "every Sunday"});

    addCheckBoxesToLayout(daysCheckBoxes, ui->verticalLayoutRepetition);
}

void AlarmEditor::setConnections()
{
    QObject::connect(ui->turnVolumeCheckBox, &QCheckBox::stateChanged, [this]{ setWidgetEnabled(ui->turnVolumeCheckBox, ui->soundVolumeSlider); });
    QObject::connect(ui->snoozeCheckBox, &QCheckBox::stateChanged, [this]{ setWidgetEnabled(ui->snoozeCheckBox, ui->snoozeComboBox); });
    QObject::connect(ui->soundVolumeSlider, &QSlider::valueChanged, this, &AlarmEditor::setValueOfProgress);
    QObject::connect(ui->btnPlay, &QPushButton::clicked, this, &AlarmEditor::playSound);
    QObject::connect(ui->btnOK, &QPushButton::clicked, this, &AlarmEditor::accept);
    QObject::connect(ui->btnCancel, &QPushButton::clicked, this, &AlarmEditor::reject);
    QObject::connect(this, &AlarmEditor::accepted, this, &AlarmEditor::createAlarm);
}

void AlarmEditor::setValueOfProgress()
{
    ui->soundValueLabel->setText(QString::number(ui->soundVolumeSlider->value()) + "%");
}

void AlarmEditor::playSound()
{
    int volume = ui->turnVolumeCheckBox->isChecked() ? ui->soundVolumeSlider->value() : 0;

    Sounds::setSettings(SoundSettings(volume, ui->soundsList->currentIndex(), 1));
    Sounds::play();
}

QVector<int> AlarmEditor::getDays()
{
    QVector<int> days;

    for(int i = 0; i < daysCheckBoxes.size(); ++i)
    {
        if(daysCheckBoxes[i]->isChecked())
        {
            days.push_back(i);
        }
    }

    return days;
}

void AlarmEditor::createAlarm()
{
    QTime time(ui->spinBoxHour->value(), ui->spinBoxMinutes->value());
    auto days = getDays();
    auto note = ui->textEditNote->toPlainText();

    alarm = Alarm(true, time, days, ui->textEditNote->toPlainText());

    alarm.setSoundSettings(SoundSettings(ui->soundVolumeSlider->value(),
                                          ui->soundsList->currentIndex(),
                                          getDuration(ui->playSoundComboBox->currentText()),
                                          ui->soundsList->currentText()));

    alarm.setSnooze(Snooze(getDuration(ui->snoozeComboBox->currentText()),
                                        ui->snoozeCheckBox->isChecked()));
}

Alarm AlarmEditor::getAlarm()
{
    return alarm;
}
