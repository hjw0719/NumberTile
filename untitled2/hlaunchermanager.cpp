#include "hlaunchermanager.h"

#include "htile.h"

HLancherManager* HLancherManager::m_singleTonManager = NULL;

HLancherManager::HLancherManager()
{
}

void HLancherManager::initialize()
{
    m_engine = new QQmlApplicationEngine;

    registerItem();
}

QQmlApplicationEngine *HLancherManager::getEngine()
{
    return m_engine;
}

HLancherManager *HLancherManager::instance()
{
    if (!m_singleTonManager)
    {
        m_singleTonManager = new HLancherManager();
    }

    return m_singleTonManager;
}

void HLancherManager::registerItem()
{
    qmlRegisterType<HTile>("HTile", 1, 0, "HTile");
    qmlRegisterType<HEnum>("HEnum", 1, 0, "HEnum");
}
