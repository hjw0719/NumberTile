import QtQuick 2.0
import QtQuick.Window 2.14
import HEnum 1.0

Item{
    id: id_mainGamePage
    width: Screen.width
    height : Screen.height

    property int tileSize : 3
    property int nLastNumber : tileSize * tileSize - 1
    property int nFirstNumber : 1
    property bool bFever : false

    onTileSizeChanged: {
        // 변경된 사이즈로 모델 초기화.
    }

    onBFeverChanged: {
        // Fever 상태 변경 동작.
        for (var i = 0; i < id_tileList.count; i++)
        {
            var item = id_tileList.itemAt(i)

            item.status = bFever ? HEnum.E_TILE_STATUS_FEVER
                                 : 0 === item.number ? HEnum.E_TILE_STATUS_VACANCY
                                                     : HEnum.E_TILE_STATUS_OCCUPY
        }
    }

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
        columns: tileSize
        height: parent.height * 0.75
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        spacing: 5

        Repeater{
            id: id_tileList
            objectName: "id_tileList"
            model : tileSize * tileSize

            delegate: Tile {
                width: (id_mainGamePage.width - id_grid.spacing * 2)/3.0
                height: (id_grid.height - id_grid.spacing * 2)/3.0

                number: index === (id_tileList.count - 1) ? 0 : index + 1
                status: index === (id_tileList.count - 1) ? HEnum.E_TILE_STATUS_VACANCY : HEnum.E_TILE_STATUS_OCCUPY

                mouseArea.onClicked: {
                    if (bFever)
                    {
                        onSuccessTouched()
                    }
                    else
                    {
                        if (number === nFirstNumber)
                        {
                            // [1] Change Last, First Number
                            nLastNumber = nLastNumber + 1;
                            nFirstNumber = nFirstNumber + 1;

                            // [2] 타일을 우선 비어있는 타일로 변경.
                            number = 0
                            status = HEnum.E_TILE_STATUS_VACANCY

                            // [3] 비어 있는 타일 찾기.
                            var vacancyItems = []
                            for (var i = 0; i < id_tileList.count; i++)
                            {
                                if (id_tileList.itemAt(i).status === HEnum.E_TILE_STATUS_VACANCY)
                                {
                                    vacancyItems.push(i)
                                }
                            }

                            var vacancyItemSize = vacancyItems.length

                            // [4] 비어 있는 타일 중 Occupy로 변경할 타일 랜덤하게 선택.
                            var convertOccupyIndex = Math.ceil(Math.random() * vacancyItemSize) - 1
                            var occupyIndex = vacancyItems[convertOccupyIndex]

                            // [5] Occupy로 변경.
                            id_tileList.itemAt(occupyIndex).number = nLastNumber
                            id_tileList.itemAt(occupyIndex).status = HEnum.E_TILE_STATUS_OCCUPY

                            onSuccessTouched()
                        }
                        else
                        {
                            onFailTouched()
                        }
                    }

                }
            }

            Component.onCompleted:
            {
                for (var i = 0; i < id_tileList.count; i++)
                {
                    // Math.random() * count : 1~count 까지 랜덤하게 숫자가 생성됨. 따라서 Index 접근을 위해 -1 필요
                    var swapA = Math.ceil(Math.random() * id_tileList.count) - 1
                    var swapB = Math.ceil(Math.random() * id_tileList.count) - 1

                    swap(swapA, swapB)
                }
            }
        }
    }

    function swap(a, b)
    {
        var tempNumber = id_tileList.itemAt(a).number
        var tempStatus = id_tileList.itemAt(a).status

        id_tileList.itemAt(a).number = id_tileList.itemAt(b).number
        id_tileList.itemAt(a).status = id_tileList.itemAt(b).status

        id_tileList.itemAt(b).number = tempNumber
        id_tileList.itemAt(b).status = tempStatus
    }

    Popup {
        strDisplayText: "Game Over!!!"
        visible: false
    }
}


