#ifndef FILE_H
#define FILE_H

#include <QVector>
#include <QFile>
#include <QTextStream>

class FileInfo
{
public:

  FileInfo() = default;

  enum class SaveStateExp
  {
      NotSaved,
      Saved,
  };

  enum class SaveStateFromBeg
  {
      NotSavedYet,
      AlreadySaved
  };

  static void setCurrentFile(const QString& current);
  static QString getCurrentFile();
  static void setSaveState(SaveStateExp state);
  static void setSaveStateFromBeg(SaveStateFromBeg state);
  static SaveStateExp getSaveState();
  static SaveStateFromBeg getSaveStateFromBeg();

private:

    static QString currentFile;
    static SaveStateExp saveState;
    static SaveStateFromBeg saveStateFromBeg;
};

class File
{
public:
    File(const QString& reqfileName, QIODevice::OpenModeFlag device);
    ~File();

    void saveAlarmSettings(bool alarmEnabled, int hour, int minutes, const QVector<int>& days, const QString& note);
    void saveSnoozeSettings(bool enabled, int duration);
    void saveSoundsSettings(int volume, int fileNumber, int duration, const QString& name);
    QStringList load();

private:

    QString fileName;
    QFile file;
    QTextStream textStream;
};

#endif // FILE_H
