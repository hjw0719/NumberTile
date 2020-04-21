import QtQuick 2.0

Page {
    id: id_titlePage


    MouseArea{
        id: id_mouseArea
        objectName: "id_mouseArea"
        anchors.fill: parent
        onClicked: clickedPage()
        signal clickedPage()
    }

    SettingButton{
        width: 60
        height: 60

        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
    }


    Text {
        id: id_titleText
        text: "NUMBER\nTILE"
        font.pixelSize: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.width/2
        horizontalAlignment: Text.AlignHCenter
        lineHeight: 2
    }

    Text {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height / 4
        text: "Touch screen for game start!"
        font.pixelSize: parent.width/15
        anchors.horizontalCenter: parent.horizontalCenter

        Timer{
            repeat : true
            interval: 500
            running: true
            onTriggered: parent.visible = !parent.visible
        }
    }



}
