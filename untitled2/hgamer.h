#ifndef HGAMER_H
#define HGAMER_H

#include <QObject>

class HGamer : public QObject
{
    Q_OBJECT
public:
    explicit HGamer(QObject *parent = NULL);

    static void doDeleteLater(HGamer *pGamer);

    void setMaxCombo(const quint16 &nMaxCombo);
    quint16 getMaxCombo();

    void setMaxScore(const qulonglong &nMaxScore);
    qulonglong getMaxScore();

    QString getName() const;
    void setName(const QString &strName);

private :
    QString m_strName;
    quint16 m_nMaxCombo;
    qulonglong m_nMaxScore;
    quint16 m_nRank;
};

#endif // HGAMER_H
