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

    void touchProcess(const HEnum::ETouchStatus &eTouchStatus);

    void setFever(const bool &bFever);
    bool getFever();

    void setScore(const qulonglong &nScore);
    qulonglong getScore();

    void setCombo(const quint16 &nCombo);
    quint16 getCombo();

    quint8 getFeverGauge() const;
    void setFeverGauge(const quint8 &nFeverGauge);

protected:
    void initialize();

signals :
    void updateUI(HEnum::EUpdateUIType eUpdateUIType);
    void feverChanged(bool bFever);

private :
    QSharedPointer<HGamer> m_pCurrentGamer;
    bool m_bFever;
    quint8 m_nFeverGauge;
    quint16 m_nCombo;
    qulonglong m_nScore;
};

#endif // HDATAMANAGER_H
