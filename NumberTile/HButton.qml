import QtQuick 2.0

Item {
    property string strButtonText: "button"
    property int buttonRaius: 20
    property bool visibleRectangle: true
    signal clicked()
    scale: id_mouseArea.pressed ? 0.8 : 1

    MouseArea {
        id: id_mouseArea
        anchors.fill: parent
        onClicked: parent.clicked()
    }

    Rectangle {
        anchors.fill: parent
        color: id_mouseArea.pressed ? "gray" : "white"
        border.color: "black"
        border.width: 1
        radius: buttonRaius
        visible: visibleRectangle
//        antialiasing: true
    }

    Text {
        id: id_text
        text: strButtonText
        anchors.centerIn: parent
        font.pixelSize: 15
        horizontalAlignment: Text.AlignHCenter
    }

}
