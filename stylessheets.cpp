#include "stylessheets.h"

QHash<QString, QString> StylesSheets::themes;
QString StylesSheets::currentTheme;
QStringList StylesSheets::keys
{
    "Light gray",
    "Dark gray",
    "Blue"
};

QStringList StylesSheets::styles
{
    R"(D:\Documents\Alarm_clock\stylesheets\light-style.css)",
    R"(D:\Documents\Alarm_clock\stylesheets\dark-style.css)",
    R"(D:\Documents\Alarm_clock\stylesheets\blue-style.css)"
};

StylesSheets::StylesSheets() { }

void StylesSheets::load()
{
    for(int i = 0; i < styles.size(); ++i)
    {
        QFile file(styles[i]);
        file.open(QIODevice::ReadOnly);

        QTextStream textStream(&file);
        QString temp = textStream.readAll();
        themes.insert(keys[i], temp);
        file.close();
    }
}

QString StylesSheets::getSelectedStyle(const QString &key)
{
    return themes[key];
}

void StylesSheets::setCurrentStyle(const QString &key)
{
    currentTheme = themes[key];
}

QString StylesSheets::getCurrentStyle()
{
    return currentTheme;
}

QString StylesSheets::getCurrentStyleName()
{
    return themes.key(currentTheme);
}
