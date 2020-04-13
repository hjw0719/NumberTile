#include "maingamepage.h"
#include "manager.h"
#include "page.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlIncubator>
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Manager::instance()->initialize();

    MainGamePage a;

    a.show();
    return app.exec();
}
