#ifndef SNOOZE_H
#define SNOOZE_H


class Snooze
{
public:

    Snooze();
    Snooze(int reqDuration, bool reqEnabled);

    bool isEnabled() const;
    bool isFinished(const int current) const;
    int getDuration() const;

private:

    int duration;
    bool enabled;
};

#endif // SNOOZE_H
