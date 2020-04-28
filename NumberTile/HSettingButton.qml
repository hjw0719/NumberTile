import QtQuick 2.0

HButton{
    id :id_settingButton
    objectName: "id_settingButton"

    strButtonText: ""
    visibleRectangle: false

    signal clickedSettingButton()

    onClicked:{
        clickedSettingButton()
    }

    Image{
        anchors.fill: parent
        source: "qrc:/image/setting.png"
    }

    Item{

    }

    Rectangle{

    }
}
