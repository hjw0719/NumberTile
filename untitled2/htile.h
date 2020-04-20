#ifndef HTILE_H
#define HTILE_H

#include <qquickitem.h>
#include "HEnum.h"

class HTile : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int number READ getNumber WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(HEnum::ETileStatus status READ getTileStatus WRITE setTileStatus NOTIFY tileStatusChanged)
public :


public:
    explicit HTile(QQuickItem *parent = NULL);
    virtual ~HTile();

    void initialize();

    uint64_t getNumber() const;
    void setNumber(QVariant vNumber);

    HEnum::ETileStatus getTileStatus() const;
    void setTileStatus(const QVariant &vState);

protected slots :
    void onSuccessTouched();
    void onFailTouched();

signals :
    void numberChanged();
    void tileStatusChanged();

private :
    uint64_t m_nNumber;
    HEnum::ETileStatus m_eTileStatus;
};



#endif // HTILE_H
