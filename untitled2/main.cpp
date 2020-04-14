#include "maingamepage.h"
#include "manager.h"
#include "page.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlIncubator>
#include <QQuickWindow>

// 우리만의 Class라는 것을 알 수 있게 앞에 H 같은걸 붙여서 파일 만들기.

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Manager::instance()->initialize();

    MainGamePage a;

    a.show();
    return app.exec();
}
