import QtQuick 2.0
import HTile 1.0
import HEnum 1.0

HTile {
    id : id_tile

    property alias mouseArea : id_mouseArea;

    Rectangle {
        id : id_background
        anchors.fill: parent
        color: HEnum.E_TILE_STATUS_FEVER === id_tile.status ? "green"
                                                            : HEnum.E_TILE_STATUS_OCCUPY === id_tile.status ? "orange"
                                                                                                            : "gray"
        opacity: 0.8
        Text {
            anchors.centerIn: parent
            text: HEnum.E_TILE_STATUS_OCCUPY === id_tile.status ? id_tile.number : ""
            font.pixelSize: 30
        }

        scale: id_mouseArea.pressed ? 0.8 : 1

        radius: 20
    }

    MouseArea {
        id : id_mouseArea
        anchors.fill: parent
    }
}
