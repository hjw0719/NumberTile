#include "hdatamanager.h"

#include "htile.h"

#define TILE_COUNT 8

QSharedPointer<HDataManager> obj = NULL;

HDataManager::HDataManager(QObject *parent) :
    QObject(parent)
{
    initialize();
}

void HDataManager::setLastNumber(const quint64 &nNumber)
{
    if (m_nLastNumber == nNumber)
    {
        return;
    }

    m_nLastNumber = nNumber;
    m_nFirstNumber = m_nLastNumber - TILE_COUNT + 1;
}

QSharedPointer<HDataManager> HDataManager::instance()
{
    if (obj.isNull())
    {
        obj = QSharedPointer<HDataManager>(new HDataManager, &HDataManager::doDelete);
    }

    return obj;
}

void HDataManager::doDelete(HDataManager *manager)
{
    if (nullptr != manager)
    {
        delete manager;
    }
}

void HDataManager::touchProcess(const HTile *tile)
{
    if (nullptr == tile)
    {
        return;
    }

    if (tile->getNumber() == m_nFirstNumber)
    {
        // SUCCESS
        // [1] 타일 변경
        // [2] 점수 산정
    }
}

void HDataManager::initialize()
{
    setLastNumber(TILE_COUNT);
}
