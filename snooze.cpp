#include "snooze.h"


Snooze::Snooze() :
    duration{},
    enabled{} { }

Snooze::Snooze(int reqDuration, bool reqEnabled) :
    Snooze{}
{
    duration = reqDuration;
    enabled = reqEnabled;
}

bool Snooze::isEnabled() const
{
    return enabled;
}

bool Snooze::isFinished(const int current) const
{

    return (current == duration);
}

int Snooze::getDuration() const
{
    return duration;
}




