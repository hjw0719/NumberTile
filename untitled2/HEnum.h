#ifndef HENUM_H
#define HENUM_H

#include <QObject>

class HEnum : public QObject
{
    Q_OBJECT
public :
    explicit HEnum() {}

public :
    enum ETouchStatus{
        E_TOUCH_STATUS_SUCCESS,
        E_TOUCH_STATUS_FAIL
    };

    Q_ENUM(ETouchStatus)

    enum ETileStatus
    {
        E_TILE_STATUS_VACANCY = 0,
        E_TILE_STATUS_OCCUPY
    };

    Q_ENUM(ETileStatus)

};

Q_DECLARE_METATYPE(HEnum::ETouchStatus);
Q_DECLARE_METATYPE(HEnum::ETileStatus);

#endif // HENUM_H
