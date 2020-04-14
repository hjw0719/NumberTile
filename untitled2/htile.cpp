#include "htile.h"

HTile::HTile(QQuickItem *parent) :
    QQuickItem(parent),
    m_nNumber(0),
    m_eTileState(E_TILE_STATE_VACANCY)
{

}

HTile::~HTile()
{

}

void HTile::initialize()
{
    m_nNumber = 0;
    m_eTileState = E_TILE_STATE_VACANCY;
}

int HTile::getNumber() const
{
    return m_nNumber;
}

void HTile::setNumber(int nNumber)
{
    m_nNumber = nNumber;
}

ETileState HTile::getTileState() const
{
    return m_eTileState;
}

void HTile::setTileState(const ETileState &eState)
{
    m_eTileState = eState;
}
