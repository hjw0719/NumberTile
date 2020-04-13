import QtQuick 2.0

Item{
    id: id_mainGamePage

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
                onClickedTile: id_tileList.clickedTileSignal(number)
            }
        }
    }
}
