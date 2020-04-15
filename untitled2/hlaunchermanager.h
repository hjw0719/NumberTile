#ifndef MANAGE_H
#define MANAGE_H

#include <QQmlApplicationEngine>

class HLancherManager
{
private:
    explicit HLancherManager();


public:
    void initialize();
    QQmlApplicationEngine *getEngine();
    static HLancherManager *instance();

protected:
    void registerItem();

private:
    QQmlApplicationEngine *m_engine;
    static HLancherManager* m_singleTonManager;
};

#endif // MANAGE_H
