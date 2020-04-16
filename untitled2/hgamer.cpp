#include "hgamer.h"

#include <QDebug>
HGamer::HGamer(QObject *parent) :
    QObject(parent),
    m_nCombo(0),
    m_nMaxCombo(0),
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

    if (getMaxScore() < m_nScore)
    {
        setMaxScore(m_nScore);
    }

    emit scoreChanged();
}

qulonglong HGamer::getScore()
{
    return m_nScore;
}

void HGamer::setCombo(const quint16 &nCombo)
{
    m_nCombo = nCombo;

    if (getMaxCombo() < m_nCombo)
    {
        setMaxCombo(m_nCombo);
    }

    emit comboChanged();
}

quint16 HGamer::getCombo()
{
    return m_nCombo;
}

void HGamer::setMaxCombo(const quint16 &nMaxCombo)
{
    m_nMaxCombo = nMaxCombo;

    qDebug() << "Max Combo : " << m_nMaxCombo;
}

quint16 HGamer::getMaxCombo()
{
    return m_nMaxCombo;
}

void HGamer::setMaxScore(const qulonglong &nMaxScore)
{
    m_nMaxScore = nMaxScore;

    qDebug() << "Max Score : " << m_nMaxScore;
}

qulonglong HGamer::getMaxScore()
{
    return m_nMaxScore;
}
