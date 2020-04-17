#include "hlaunchermanager.h"

#include "htile.h"
#include "maingamepage.h"
#include "HDefine.h"
HLancherManager* HLancherManager::m_singleTonManager = NULL;

HLancherManager::HLancherManager()
{
}

void HLancherManager::initialize()
{
    m_engine = new QQmlApplicationEngine;

    m_pWindow = new QQuickWindow;
    registerItem();

    MainGamePage *pMainGamePage = new MainGamePage;
    pMainGamePage->setParentItem(m_pWindow->contentItem());

#ifdef Q_OS_WIN
    m_pWindow->setWidth(DESKTOP_OS_WIDTH);
    m_pWindow->setHeight(DESKTOP_OS_HEIGHT);
#endif
    m_pWindow->show();
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
