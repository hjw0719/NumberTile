#ifndef HENUM_H
#define HENUM_H

#include <QObject>

class HEnum : public QObject
{
    Q_OBJECT
public :
    explicit HEnum() {}

public :

    enum EUpdateUIType{
        E_UPDATE_UI_SUCCESS_TOUCH,
        E_UPDATE_UI_FAIL_TOUCH,
        E_UPDATE_UI_FEVER,
        E_UPDATE_UI_NORMAL
    };

    Q_ENUM(EUpdateUIType)

    enum ETouchStatus{
        E_TOUCH_STATUS_SUCCESS,
        E_TOUCH_STATUS_FAIL
    };

    Q_ENUM(ETouchStatus)

    enum ETileStatus
    {
        E_TILE_STATUS_VACANCY = 0,
        E_TILE_STATUS_OCCUPY,
        E_TILE_STATUS_FEVER
    };

    Q_ENUM(ETileStatus)

};

// Qt가 해당 enum값을 알 수 있게 등록.
// ex) QVariant val;
//     val.canConvert<HEnum::ETouchStatus>() << 이렇게 사용할 수 있도록 해줌.
Q_DECLARE_METATYPE(HEnum::EUpdateUIType);
Q_DECLARE_METATYPE(HEnum::ETouchStatus);
Q_DECLARE_METATYPE(HEnum::ETileStatus);

#endif // HENUM_H
