QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activealarm.cpp \
    activealarmdetector.cpp \
    alarm.cpp \
    alarmeditor.cpp \
    alarmscollection.cpp \
    deserialization.cpp \
    duration.cpp \
    file.cpp \
    floatingwindowclock.cpp \
    main.cpp \
    mainwindow.cpp \
    previewwidget.cpp \
    snooze.cpp \
    sounds.cpp \
    stylesheeteditor.cpp \
    stylessheets.cpp \
    table.cpp \
    tableactionmenu.cpp \
    week.cpp

HEADERS += \
    activealarm.h \
    activealarmdetector.h \
    alarm.h \
    alarmeditor.h \
    alarmscollection.h \
    deserialization.h \
    duration.h \
    file.h \
    floatingwindowclock.h \
    functions.h \
    mainwindow.h \
    previewwidget.h \
    snooze.h \
    sounds.h \
    stylesheeteditor.h \
    stylessheets.h \
    table.h \
    tableactionmenu.h \
    tableitemsimpl.h \
    week.h

FORMS += \
    activealarm.ui \
    alarmeditor.ui \
    floatingwindowclock.ui \
    mainwindow.ui \
    previewwidget.ui \
    stylesheeteditor.ui \
    table.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=
