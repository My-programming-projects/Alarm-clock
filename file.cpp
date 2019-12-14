#include "file.h"
#include <QMessageBox>

QString FileInfo::currentFile = " ";
FileInfo::SaveStateExp FileInfo::saveState = FileInfo::SaveStateExp::Saved;
FileInfo::SaveStateFromBeg FileInfo::saveStateFromBeg = FileInfo::SaveStateFromBeg::NotSavedYet;

void FileInfo::setCurrentFile(const QString &current)
{
    currentFile = current;
}

QString FileInfo::getCurrentFile()
{
    return currentFile;
}

void FileInfo::setSaveState(SaveStateExp state)
{
    saveState = state;
}

FileInfo::SaveStateExp FileInfo::getSaveState()
{
    return saveState;
}

void FileInfo::setSaveStateFromBeg(SaveStateFromBeg state)
{
    saveStateFromBeg = state;
}

FileInfo::SaveStateFromBeg FileInfo::getSaveStateFromBeg()
{
    return saveStateFromBeg;
}

/////////////////////////////

File::File(const QString& reqFileName, QIODevice::OpenModeFlag device) :
    fileName(reqFileName),
    file(fileName),
    textStream(&file)
{
    file.open(device);
}

File::~File()
{
    file.close();
}

void File::saveAlarmSettings(bool alarmEnabled, int hour, int minutes, const QVector<int> &days, const QString &note)
{
    textStream << '|' << alarmEnabled << '|' << hour << '|' << minutes << '|';

    for(int i = 0; i < days.size(); ++i)
    {
        textStream << days[i];
    }

    textStream << '|' << note;
}

void File::saveSnoozeSettings(bool enabled, int duration)
{
    textStream << '|' << enabled << '|' << duration;
}

void File::saveSoundsSettings(int volume, int fileNumber, int duration, const QString &name)
{
    textStream << '|' << volume << '|' << fileNumber << '|' << duration << '|' << name << '|' << '\n';
}

QStringList File::load()
{
    QStringList data;

    while(!file.atEnd())
    {
        QString helper = file.readLine();
        data.push_back(helper);
    }

    //QString str = file.readLine();

    return data;
    //return str;
}
