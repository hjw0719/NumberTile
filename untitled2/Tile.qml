import QtQuick 2.0
import HTile 1.0

HTile {
    id : id_tile

    property alias mouseArea : id_mouseArea;

    Rectangle {
        anchors.fill: parent
        color: HTile.E_TILE_STATUS_OCCUPY === id_tile.status ? "yellow" : "gray"
        opacity: 0.8
        Text {
            anchors.centerIn: parent
            text: HTile.E_TILE_STATUS_OCCUPY === id_tile.status ? id_tile.number : ""
            font.pixelSize: 30
        }
    }

    MouseArea {
        id : id_mouseArea
        anchors.fill: parent
    }
}
