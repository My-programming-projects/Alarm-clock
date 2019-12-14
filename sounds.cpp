#include "sounds.h"

SoundSettings::SoundSettings() :
    volume{},
    notConvertedVolume{},
    soundFileNumber{},
    duration{} { }

SoundSettings::SoundSettings(int reqVolume, int reqFileNumber, int reqDuration) :
    volume{convertToQReal(reqVolume)},
    notConvertedVolume{reqVolume},
    soundFileNumber{reqFileNumber},
    duration{reqDuration},
    name{" "} { }

SoundSettings::SoundSettings(int reqVolume, int reqFileNumber, int reqDuration, const QString& reqName) :
    SoundSettings{reqVolume, reqFileNumber, reqDuration}
{
    name = reqName;
}

qreal SoundSettings::convertToQReal(int vol)
{
    return QAudio::convertVolume(vol / qreal(100.0), QAudio::LogarithmicVolumeScale,
                                 QAudio::LinearVolumeScale);
}

qreal SoundSettings::getVolume() const
{
    return volume;
}

int SoundSettings::getNotConvertedVolume() const
{
    return notConvertedVolume;
}

int SoundSettings::getFileNumber() const
{
    return soundFileNumber;
}

int SoundSettings::getDuration() const
{
    return duration;
}

QString SoundSettings::getName() const
{
    return name;
}

//////////////////////////////////////////////////////////////////////////////////////

QStringList Sounds::soundsFileNames
{
    R"(D:\Documents\Alarm_clock\sounds\Alarm1.wav)",
    R"(D:\Documents\Alarm_clock\sounds\Alarm2.wav)",
    R"(D:\Documents\Alarm_clock\sounds\Alarm3.wav)",
    R"(D:\Documents\Alarm_clock\sounds\Alarm4.wav)"
};

int Sounds::fileNumber;

QSoundEffect Sounds::soundEffect;

void Sounds::setSettings(const SoundSettings &soundSettings)
{
    soundEffect.setVolume(soundSettings.getVolume());
    soundEffect.setLoopCount(soundSettings.getDuration());
    soundEffect.setSource(QUrl::fromLocalFile(soundsFileNames[soundSettings.getFileNumber()]));
}

void Sounds::play()
{
    soundEffect.play();
}

void Sounds::stop()
{
    soundEffect.stop();
}

bool Sounds::isFinished()
{
    return !soundEffect.isPlaying();
}
