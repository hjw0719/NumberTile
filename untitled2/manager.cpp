#include "manager.h"


Manager* Manager::m_singleTonManager = NULL;

Manager::Manager()
{
}

void Manager::initialize()
{
    m_engine = new QQmlApplicationEngine;
}

QQmlApplicationEngine *Manager::getEngine()
{
    return m_engine;
}

Manager *Manager::instance()
{
    if (!m_singleTonManager)
    {
        m_singleTonManager = new Manager();
    }

    return m_singleTonManager;
}
