#include "hgamer.h"

#include <QDebug>
HGamer::HGamer(QObject *parent) :
    QObject(parent),
    m_nMaxCombo(0),
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

void HGamer::setMaxCombo(const quint16 &nMaxCombo)
{
    if (m_nMaxCombo < nMaxCombo)
    {
        m_nMaxCombo = nMaxCombo;
    }
}

quint16 HGamer::getMaxCombo()
{
    return m_nMaxCombo;
}

void HGamer::setMaxScore(const qulonglong &nMaxScore)
{
    if (m_nMaxScore < nMaxScore)
    {
        m_nMaxScore = nMaxScore;
    }
}

qulonglong HGamer::getMaxScore()
{
    return m_nMaxScore;
}
