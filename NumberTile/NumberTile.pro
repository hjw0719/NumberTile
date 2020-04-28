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


COM_MKDIR = ""
DEST_FONT = ""

# 안드로이드 관련 파일 생성 위치 지정.
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

# 빌드하는 환경이 윈도우인 경우.
equals (QMAKE_HOST.os, "Windows") {

        # 폴더 생성 명령어를 윈도우 용으로 설정
        COM_MKDIR = MKDIR

        # 빌드를 Debug or Release로 할 때 실행 파일 위치에 따라 font 복사 경로 다르게 지정.
        CONFIG(debug, debug|release) {
                DEST_FONT = $$shell_path($$OUT_PWD/debug/resource/font)
        } else {
                DEST_FONT = $$shell_path($$OUT_PWD/release/resource/font)
        }
}

# 폰트 폴더가 존재하지 않는 경우 폴더 생성
!exists($$shell_path($$DEST_FONT)) {
        AAA = $$system($$COM_MKDIR $$DEST_FONT)
}

# 원본 소스에서 폰트 파일을 빌드한 곳으로 복사
equals (QMAKE_HOST.os, "Windows") {
    copyFontFolder.target = copyFontFolder
    copyFontFolder.commands = $(COPY_DIR) $$shell_path($$PWD/resource/font) $$DEST_FONT
    QMAKE_EXTRA_TARGETS += copyFontFolder
    PRE_TARGETDEPS += copyFontFolder
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    resource/AndroidManifest.xml \
    resource/build.gradle \
    resource/gradle/wrapper/gradle-wrapper.jar \
    resource/gradle/wrapper/gradle-wrapper.properties \
    resource/gradlew \
    resource/gradlew.bat \
    resource/res/values/libs.xml


