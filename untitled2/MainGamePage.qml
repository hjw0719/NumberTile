import QtQuick 2.0
import QtQuick.Window 2.14

Item{
    id: id_mainGamePage
    width: Screen.width
    height : Screen.height

    Grid{
        columns: 3
        Repeater{
            id: id_tileList
            objectName: "id_tileList"
            signal clickedTileSignal(int nIndex)

            delegate: Tile {
                width: id_mainGamePage.width/3.0
                height: id_mainGamePage.height/3.0

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
