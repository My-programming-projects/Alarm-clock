#include "week.h"


QStringList Week::days
{
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun"
};

QString Week::getDay(int index)
{
    return days[index];
}
