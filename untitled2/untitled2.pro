QT += quick multimedia

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        hdatamanager.cpp \
        hgamer.cpp \
        hlaunchermanager.cpp \
        hpage.cpp \
        hsettingmanager.cpp \
        hsettingpage.cpp \
        htile.cpp \
        hwindow.cpp \
        main.cpp \
        maingamepage.cpp \
        scoreboardpage.cpp \
        titlepage.cpp

RESOURCES += qml.qrc \
    resource/resource.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


equals (QMAKE_HOST.os, "Windows") {
        DEFINES += OS_DESKTOP
}

VERSION = 0.1.0.30

HEADERS += \
    HDefine.h \
    HEnum.h \
    hdatamanager.h \
    hgamer.h \
    hlaunchermanager.h \
    hpage.h \
    hsettingmanager.h \
    hsettingpage.h \
    htile.h \
    hwindow.h \
    maingamepage.h \
    scoreboardpage.h \
    titlepage.h
