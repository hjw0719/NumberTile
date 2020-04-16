#ifndef HTILE_H
#define HTILE_H

#include <qquickitem.h>


class HTile : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int number READ getNumber WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(ETileStatus status READ getTileStatus WRITE setTileStatus NOTIFY tileStatusChanged)
public :
    enum ETileStatus
    {
        E_TILE_STATUS_VACANCY = 0,
        E_TILE_STATUS_OCCUPY
    };

    Q_ENUM(ETileStatus)


public:
    explicit HTile(QQuickItem *parent = NULL);
    virtual ~HTile();

    void initialize();

    quint64 getNumber() const;
    void setNumber(QVariant vNumber);

    HTile::ETileStatus getTileStatus() const;
    void setTileStatus(const QVariant &vState);

protected slots :
    void onSuccessTouched();
    void onFailTouched();

signals :
    void numberChanged();
    void tileStatusChanged();

private :
    quint64 m_nNumber;
    ETileStatus m_eTileStatus;
};

Q_DECLARE_METATYPE(HTile::ETileStatus);

#endif // HTILE_H
