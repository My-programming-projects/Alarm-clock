#ifndef THEMESCOLLECTION_H
#define THEMESCOLLECTION_H

#include <QHash>
#include <QStringList>
#include <QFile>
#include <QTextStream>

class StylesSheets
{
public:

    enum DataType
    {
        Key,
        Value
    };

    StylesSheets();
    StylesSheets(const StylesSheets& copy) = delete;
    StylesSheets(StylesSheets&& move) = delete;

    StylesSheets& operator=(const StylesSheets& rhs) = delete;
    StylesSheets& operator=(StylesSheets&& rhs) = delete;

    static void setCurrentStyle(const QString& key);
    static QString getSelectedStyle(const QString& key);
    static QString getCurrentStyle();
    static QString getCurrentStyleName();
    static void load();

private:

    static QStringList styles;
    static QStringList keys;
    static QHash<QString, QString> themes;
    static QString currentTheme;
};

///////////////////////////////////////////////////////////////

template<typename Widget>
void setUpdatedStyleSheet(Widget* widget)
{
    widget->setStyleSheet(StylesSheets::getCurrentStyle());
}

template<typename Widget, typename... Widgets>
void setUpdatedStyleSheet(Widget* widget, Widgets... widgets)
{
    widget->setStyleSheet(StylesSheets::getCurrentStyle());
    setUpdatedStyleSheet(widgets...);
}

#endif // THEMESCOLLECTION_H
