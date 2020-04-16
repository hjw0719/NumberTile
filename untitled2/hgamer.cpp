#include "hgamer.h"

HGamer::HGamer(QObject *parent) :
    QObject(parent),
    m_nCombo(0),
    m_nScore(0),
    m_nMaxScore(0),
    m_nRank(0)
{

}

void HGamer::doDeleteLater(HGamer *pGamer)
{
    if (!pGamer)
    {
        return;
    }

    pGamer->deleteLater();
}

void HGamer::setScore(const qulonglong &nScore)
{
    m_nScore = nScore;
}

qulonglong HGamer::getScore()
{
    return m_nScore;
}

void HGamer::setCombo(const quint16 &nCombo)
{
    m_nCombo = nCombo;
}

quint16 HGamer::getCombo()
{
    return m_nCombo;
}

void HGamer::setMaxScore(const qulonglong &nMaxScore)
{
    m_nMaxScore = nMaxScore;
}

qulonglong HGamer::getMaxScore()
{
    return m_nMaxScore;
}
