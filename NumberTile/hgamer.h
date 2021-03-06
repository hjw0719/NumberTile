#ifndef HGAMER_H
#define HGAMER_H

#include <QJsonObject>
#include <QObject>

class HGamer : public QObject
{
    Q_OBJECT
public:
    explicit HGamer(QObject *parent = NULL);
    virtual ~HGamer() {}

    static void doDeleteLater(HGamer *pGamer);
    QJsonObject toJson();

public : //getter setter

    void setMaxCombo(const uint16_t &nMaxCombo);
    uint16_t getMaxCombo();

    void setMaxScore(const uint64_t &nMaxScore);
    uint64_t getMaxScore();

    QString getName() const;
    void setName(const QString &strName);

    uint16_t getRank() const;
    void setRank(const uint16_t &nRank);

    uint64_t getMaxTileNumber() const;
    void setMaxTileNumber(const uint64_t &nMaxTileNumber);

//    HGamer &operator=(const HGamer &gamer);

private :
    QString m_strName;
    uint16_t m_nMaxCombo;
    uint64_t m_nMaxScore;
    uint16_t m_nRank;
    uint64_t m_nMaxTileNumber;
};


#endif // HGAMER_H
