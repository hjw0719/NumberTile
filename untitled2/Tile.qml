import QtQuick 2.0

Item {

    property int number: 0
    property int nState: 0
    signal clickedTile(int number)

    Rectangle {
        visible: nState
        anchors.fill: parent
        color: "yellow"
        opacity: 0.8
        Text {
            anchors.centerIn: parent
            text: number
            font.pixelSize: 30
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: clickedTile(number)
    }
}
