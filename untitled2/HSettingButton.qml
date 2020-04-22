import QtQuick 2.0

HButton{
    id :id_settingButton
    objectName: "id_settingButton"

    strButtonText: "Setting"

    signal clickedSettingButton()

    onClicked:{
        clickedSettingButton()
    }
}
