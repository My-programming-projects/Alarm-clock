#ifndef SOUNDS_H
#define SOUNDS_H

#include <QSoundEffect>
#include <QAudio>
#include <QStringList>

#include "duration.h"

class SoundSettings
{
public:

    SoundSettings();
    SoundSettings(int reqVolume, int reqFileNumber, int reqDuration);
    SoundSettings(int reqVolume, int reqFileNumber, int reqDuration, const QString& reqName);

    qreal getVolume() const;
    int getNotConvertedVolume() const;
    int getFileNumber() const;
    int getDuration() const;
    QString getName() const;

private:

    qreal convertToQReal(int vol);

    qreal volume;
    int notConvertedVolume;
    int soundFileNumber;
    int duration;
    QString name;
};

///////////////////////////

class Sounds
{
public:

    Sounds() = default;

    static void setSettings(const SoundSettings& soundSettings);
    static void play();
    static void stop();
    static bool isFinished();

private:

    static QStringList soundsFileNames;
    static QSoundEffect soundEffect;
    static int fileNumber;
};

#endif // SOUNDS_H
