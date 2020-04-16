#ifndef HDATAMANAGER_H
#define HDATAMANAGER_H

#include <QList>
#include <QSharedPointer>

class HGamer;
class HTile;

class HDataManager : public QObject
{
    Q_OBJECT
public:
    explicit HDataManager(QObject *parent = NULL);

    void setLastNumber(const quint64 &nNumber);

    static QSharedPointer<HDataManager> instance();
    static void doDelete(HDataManager *manager);

    void touchProcess(const HTile *tile);

protected:
    void initialize();

private :
    quint64 m_nFirstNumber;
    quint64 m_nLastNumber;
};

#endif // HDATAMANAGER_H
