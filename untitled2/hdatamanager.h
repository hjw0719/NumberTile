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

    qulonglong getScore();
    quint16 getCombo();
protected:
    void initialize();

signals :
    void updateUI(HEnum::ETouchStatus eTouchStatus);

private :
    QSharedPointer<HGamer> m_pCurrentGamer;
};

#endif // HDATAMANAGER_H
