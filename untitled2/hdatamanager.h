#ifndef HDATAMANAGER_H
#define HDATAMANAGER_H

#include <QList>
#include <QSharedPointer>
#include "HEnum.h"

class HGamer;
class HTile;
// 게임 데이터 관련 처리.
class HDataManager : public QObject
{
    Q_OBJECT
public :


public:
    explicit HDataManager(QObject *parent = NULL);

    static HDataManager *instance();
    static void doDelete(HDataManager *manager);

public : // getter setter

    void setFever(const bool &bFever);
    bool getFever();

    void setScore(const uint64_t &nScore);
    uint64_t getScore();

    void setCombo(const uint16_t &nCombo);
    uint16_t getCombo();

    void setMaxCombo(const uint16_t &nMaxCombo);
    uint16_t getMaxCombo();

    uint8_t getFeverGauge() const;
    void setFeverGauge(const uint8_t &nFeverGauge);

    uint64_t getTileNumber() const;
    void setTileNumber(const uint64_t &nTileNumber);

public : // data process

    /**
     * @brief touchProcess
     *        This function react when tile touched.
     * @param eTouchStatus :
     * @param nTileNumber
     */
    void touchProcess(const HEnum::ETouchStatus &eTouchStatus, const uint64_t &nTileNumber = 0);

    void dataInitialize();

    void saveData();

    QJsonArray convertRankListToJsonArray();

    static bool highScoreThan(const QSharedPointer<HGamer> &pGamer1, const QSharedPointer<HGamer> &pGamer2);

protected:
    void initialize();
    void calculateRank(QSharedPointer<HGamer> pGamer);

signals :
    void updateUI(HEnum::EUpdateUIType eUpdateUIType);
    void feverChanged(bool bFever);

private :
//    QSharedPointer<HGamer> m_pCurrentGamer; // DB 시스템 들어가면 사용 예정.
    bool m_bFever;
    uint8_t m_nFeverGauge;
    uint16_t m_nCombo;
    uint16_t m_nMaxCombo;
    uint64_t m_nScore;
    uint64_t m_nTileNumber;
    QList<QSharedPointer<HGamer>> m_tRankList;
};

#endif // HDATAMANAGER_H
