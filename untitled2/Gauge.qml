import QtQuick 2.0

Item {
    property real fPercent: 0.3
    Rectangle{
        id: id_BG
        color: "red"
        anchors.fill: parent
    }

    Rectangle{
        id: id_gage
        anchors.left: id_BG.left
        width: parent.width * fPercent
        height: parent.height
        color: "blue"
    }
}
