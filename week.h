#ifndef WEEK_H
#define WEEK_H

#include <QStringList>


class Week
{
public:

    Week() = default;

    static QString getDay(int index);

private:

    static QStringList days;
};

#endif // WEEK_H
