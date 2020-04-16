#ifndef HDATAMANAGER_H
#define HDATAMANAGER_H

#include <QList>
#include <QSharedPointer>

class HGamer;
class HTile;
// 게임 데이터 관련 처리.
class HDataManager : public QObject
{
    Q_OBJECT
public :
    enum ETouchStatus{
        E_TOUCH_STATUS_SUCCESS,
        E_TOUCH_STATUS_FAIL
    };

    Q_ENUM(ETouchStatus)

public:
    explicit HDataManager(QObject *parent = NULL);

    static QSharedPointer<HDataManager> instance();
    static void doDelete(HDataManager *manager);

    void touchProcess(const ETouchStatus &eTouchStatus);

protected:
    void initialize();

signals :
    void successTouched();
    void failedTouched();

private :
    QSharedPointer<HGamer> m_pCurrentGamer;
};

#endif // HDATAMANAGER_H
