#ifndef HTILE_H
#define HTILE_H

#include <qquickitem.h>


enum ETileState
{
    E_TILE_STATE_VACANCY = 0,
    E_TILE_STATE_OCCUPY
};

class HTile : public QQuickItem
{
    Q_OBJECT
public:
    explicit HTile(QQuickItem *parent = NULL);
    virtual ~HTile();

    void initialize();

    int getNumber() const;
    void setNumber(int nNumber);

    ETileState getTileState() const;
    void setTileState(const ETileState &eState);

private :
    int m_nNumber;
    ETileState m_eTileState;
};

#endif // HTILE_H
