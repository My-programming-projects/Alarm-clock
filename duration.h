#ifndef DURATION_H
#define DURATION_H

#include <QHash>
#include <QVector>

using Pair = std::pair<QString, int>;

class Duration
{
public:

    Duration() = default;
    Duration(const Duration& copy) = delete;
    Duration& operator=(const Duration& rhs) = delete;

    static Pair find(const QString& key);
    static int get(const QString key);

private:

    static QHash<QString, int> seconds;
};

#endif // DURATION_H
