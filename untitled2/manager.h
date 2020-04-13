#ifndef MANAGE_H
#define MANAGE_H

#include <QQmlApplicationEngine>

class Manager
{
private:
    Manager();


public:
    void initialize();
    QQmlApplicationEngine *getEngine();
    static Manager *instance();



private:
    QQmlApplicationEngine *m_engine;
    static Manager* m_singleTonManager;
};

#endif // MANAGE_H
