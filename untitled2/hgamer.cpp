#include "hgamer.h"

#include <QString>
#include <QDebug>
HGamer::HGamer(QObject *parent) :
    QObject(parent),
    m_strName(),
    m_nMaxCombo(0),
    m_nMaxScore(0),
    m_nRank(0),
    m_nMaxTileNumber(0)
{
    m_strName = QString("aaa");
}

void HGamer::doDeleteLater(HGamer *pGamer)
{
    if (!pGamer)
    {
        return;
    }

    pGamer->deleteLater();
}

void HGamer::setMaxCombo(const uint16_t &nMaxCombo)
{
    if (m_nMaxCombo < nMaxCombo)
    {
        m_nMaxCombo = nMaxCombo;
    }
}

uint16_t HGamer::getMaxCombo()
{
    return m_nMaxCombo;
}

void HGamer::setMaxScore(const uint64_t &nMaxScore)
{
    if (m_nMaxScore < nMaxScore)
    {
        m_nMaxScore = nMaxScore;
    }
}

uint64_t HGamer::getMaxScore()
{
    return m_nMaxScore;
}

QString HGamer::getName() const
{
    return m_strName;
}

void HGamer::setName(const QString &strName)
{
    m_strName = strName;
}

//HGamer &HGamer::operator=(const HGamer &gamer)
//{
//    m_strName = gamer.m_strName;
//    m_nMaxScore = gamer.m_nMaxScore;
//    m_nMaxCombo = gamer.m_nMaxCombo;
//    m_nRank = gamer.m_nRank;

//    return *this;
//}

uint16_t HGamer::getRank() const
{
    return m_nRank;
}

void HGamer::setRank(const uint16_t &nRank)
{
    m_nRank = nRank;
}

QJsonObject HGamer::toJson()
{
    QJsonObject tempJson;
    tempJson["name"] = getName();
    tempJson["score"] = QString::number(getMaxScore());
    tempJson["tile"] = QString::number(getMaxTileNumber());
    tempJson["rank"] = getRank();

    return tempJson;
}

uint64_t HGamer::getMaxTileNumber() const
{
    return m_nMaxTileNumber;
}

void HGamer::setMaxTileNumber(const uint64_t &nMaxTileNumber)
{
    m_nMaxTileNumber = nMaxTileNumber;
}
