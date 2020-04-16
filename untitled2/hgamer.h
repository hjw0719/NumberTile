#ifndef HGAMER_H
#define HGAMER_H

#include <QObject>

class HGamer : public QObject
{
    Q_OBJECT
public:
    explicit HGamer(QObject *parent = NULL);

    static void doDeleteLater(HGamer *pGamer);

    void setScore(const qulonglong &nScore);
    qulonglong getScore();

    void setCombo(const quint16 &nCombo);
    quint16 getCombo();

    void setMaxScore(const qulonglong &nMaxScore);
    qulonglong getMaxScore();

private :
    quint16 m_nCombo;
    qulonglong m_nScore;
    qulonglong m_nMaxScore;
    quint16 m_nRank;
};

#endif // HGAMER_H
