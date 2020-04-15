#ifndef HTILE_H
#define HTILE_H

#include <qquickitem.h>



class HTile : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int number READ getNumber WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(ETileState state READ getTileState WRITE setTileState NOTIFY tileStateChanged)
public :
    enum ETileState
    {
        E_TILE_STATE_VACANCY = 0,
        E_TILE_STATE_OCCUPY
    };

    Q_ENUM(ETileState)

public:
    explicit HTile(QQuickItem *parent = NULL);
    virtual ~HTile();

    void initialize();

    int getNumber() const;
    void setNumber(int nNumber);

    HTile::ETileState getTileState() const;
    void setTileState(const HTile::ETileState &eState);

protected slots :

signals :
    void numberChanged();
    void tileStateChanged();

private :
    int m_nNumber;
    ETileState m_eTileState;
};

#endif // HTILE_H
