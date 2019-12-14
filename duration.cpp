#include "duration.h"

QHash<QString, int> Duration::seconds
{
    Pair("Until alarm message is closed", std::numeric_limits<int>::max()),
    Pair("1 second", 1),
    Pair("1 minute", 60),
    Pair("2 minutes", 120),
    Pair("3 minutes", 180),
    Pair("4 minutes", 240),
    Pair("5 minutes", 300),
    Pair("6 minutes", 360),
    Pair("7 minutes", 420),
    Pair("8 minutes", 480),
    Pair("9 minutes", 540),
    Pair("10 minutes", 600),
    Pair("15 minutes", 900),
    Pair("30 minutes", 1800),
    Pair("1 hour", 3600),
};

Pair Duration::find(const QString& key)
{
    Pair found;

    for(auto iter = seconds.begin(); iter != seconds.end(); ++iter)
    {
        if(key == iter.key())
        {
            found = std::make_pair(iter.key(), iter.value());
            break;
        }
    }

    return found;
}

int Duration::get(const QString key)
{    
    return seconds[key];
}
