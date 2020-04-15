import QtQuick 2.0
import QtQuick.Window 2.14

Item{
    id: id_mainGamePage
    width: Screen.width
    height : Screen.height

    Gauge{
        id: id_lifeGauge
        objectName: "id_lifeGauge"
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.rightMargin: 20
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 10
        height: parent.height/15.0
    }

    Grid{
        id : id_grid
        columns: 3
        height: parent.height * 0.75
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        spacing: 5
        Repeater{
            id: id_tileList
            objectName: "id_tileList"
            signal clickedTileSignal(int nIndex)

            delegate: Tile {
                width: (id_mainGamePage.width - id_grid.spacing * 2)/3.0
                height: (id_grid.height - id_grid.spacing * 2)/3.0

                number: nNumber
                nState: eState
                onClickedTile: id_tileList.clickedTileSignal(index)
            }
        }
    }

    Popup {
        strDisplayText: "Game Over!!!"
        visible: false
    }
}
