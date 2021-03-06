import QtQuick 2.0

import HEnum 1.0

Page{
    id: id_mainGamePage

    property int tileSizeX : 3
    property int tileSizeY : 3
    property int nLastNumber : tileSizeX * tileSizeY - 1
    property int nFirstNumber : nLastNumber + 2 - (tileSizeX * tileSizeY)
    property bool bFever : false

    readonly property int screenLeftMargin: 20
    readonly property int screenRightMargin: 20
    readonly property int screenTopMargin: 20
    readonly property int screenBottomMargin: 20

    onTileSizeXChanged: {
        // 변경된 사이즈로 모델 초기화.
    }

    onTileSizeYChanged: {
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

    BackGround{
        anchors.fill: parent
    }

    HButton{
        id: id_pauseButton
        objectName: "id_pauseButton"
        width: parent.width / 10
        height: parent.width / 10
        anchors.right: parent.right
        anchors.rightMargin: screenRightMargin
        anchors.bottom: id_lifeGauge.top
        anchors.bottomMargin: 5
        visibleRectangle: false
        strButtonText: ""
        Image{
            anchors.fill: parent
            source: "qrc:/image/pause.png"
        }
    }

    Text{
        id: id_score
        objectName: "id_score"
        font.pixelSize: parent.width/20
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: "0"
        color: "white"
    }

    HGauge{
        id: id_lifeGauge
        objectName: "id_lifeGauge"
//        width: parent.width * 0.7
        anchors.leftMargin: screenLeftMargin
        anchors.left: parent.left
        anchors.rightMargin: screenRightMargin
        anchors.right: parent.right
        anchors.top: id_score.bottom
        anchors.topMargin: 10
        height: parent.height/20.0
    }

    Text {
        id: id_combo
        objectName: "id_combo"
        anchors.horizontalCenter: parent.horizontalCenter
        property var combo : 0
        property int defaultFontSize:20
        property int normalMaxFontSize:30
        property int feverMaxFontSize:50

        font.pointSize: defaultFontSize
        text: combo + " COMBO!!"
        color: "white"
        visible: combo

        height: parent.height/20.0
        verticalAlignment: Text.AlignVCenter

        anchors.top: id_lifeGauge.bottom
        anchors.bottomMargin: 20
        onTextChanged: {
            if (combo)
            {
                font.pixelSize = 20
                id_comboIncreaseAnimation.stop()
                id_comboIncreaseAnimation.start()
            }
        }

        SequentialAnimation {
            id: id_comboIncreaseAnimation
            PropertyAnimation{
                target: id_combo
                property: "font.pixelSize"
                to: bFever ? id_combo.feverMaxFontSize : id_combo.normalMaxFontSize
                duration: 100
            }
            PropertyAnimation{
                target: id_combo
                property: "font.pixelSize"
                to: id_combo.defaultFontSize
                duration: 100
            }
        }


    }

    Grid{
        id : id_grid
        rows: tileSizeY
        columns: tileSizeX
        height: parent.height * 0.6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: screenBottomMargin
        anchors.left: parent.left
        anchors.leftMargin: screenLeftMargin
        anchors.right: parent.right
        anchors.rightMargin: screenRightMargin
        spacing: 5

        Repeater{
            id: id_tileList
            objectName: "id_tileList"
            model : tileSizeX * tileSizeY

            delegate: Tile {
                width: (id_grid.width - id_grid.spacing * (tileSizeX -1 ))/tileSizeX
                height: (id_grid.height - id_grid.spacing * (tileSizeY - 1))/tileSizeY

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
                            onSaveTileNumber()

                            // [1] Change Last, First Number
                            nLastNumber = nLastNumber + 1;

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
                mixTile()
            }

            function mixTile()
            {
                var count = id_tileList.count
                for (var i = 0; i < count; i++)
                {
                    // Math.random() * count : 1~count 까지 랜덤하게 숫자가 생성됨. 따라서 Index 접근을 위해 -1 필요
                    var swapA = Math.ceil(Math.random() * count) - 1
                    var swapB = Math.ceil(Math.random() * count) - 1

                    swap(swapA, swapB)
                }
            }

            function initData()
            {
                // init Last Number;
                nLastNumber = tileSizeX * tileSizeY - 1

                // init Tile
                var count = id_tileList.count
                for (var i = 0; i < count; i++)
                {
                    id_tileList.itemAt(i).number = i === (count - 1) ? 0 : i + 1
                    id_tileList.itemAt(i).status = i === (count - 1) ? HEnum.E_TILE_STATUS_VACANCY : HEnum.E_TILE_STATUS_OCCUPY
                }

                mixTile()
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

    PopupLayer {
        id: id_gamaOverPopup
        property string strDisplayText: "GAME OVER"
        property string strScore: "0"
        property string strMaxCombo: "0"
        objectName: "id_gamaOverPopup"
        visible: false

        signal clickedRestartButton()
        signal clickedScoreBoardButton()

        Rectangle {
            height: parent.height/2
            width: parent.width/1.5
            anchors.centerIn: parent

            Text {
                id: id_gameOverText
                text: id_gamaOverPopup.strDisplayText
                font.pixelSize: 30
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: parent.height / 6
            }

            Text {
                id: id_recordText
                text : "Score : " + id_gamaOverPopup.strScore + "\nMaxCombo : " + id_gamaOverPopup.strMaxCombo
                anchors.top: id_gameOverText.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 25
            }

            HButton {
                id: id_restartButton
                width: parent.width /3
                height: parent.height /3
                strButtonText: "Restart"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: parent.width/10
                onClicked:{
                    console.log("id_restartButton")
                    id_gamaOverPopup.clickedRestartButton()
                }
            }

            HButton {
                id: id_moveScoreBoard
                width: parent.width /3
                height: parent.height /3
                strButtonText: "Score\nBoard"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: parent.width/10
                onClicked:{
                    console.log("id_moveScoreBoard")
                    id_gamaOverPopup.clickedScoreBoardButton()
                }
            }
        }
    }


    PopupLayer {
        id: id_readyCount
        objectName: "id_readyCount"
        property int readyCountNumber: 2
        signal countOver()
        visible: false

        onReadyCountNumberChanged: {
            if (readyCountNumber)
            {
                visible = true
            }

            id_readyCountChangeTimer.start()
        }

        Text {
            id: id_readyCountNumber
            anchors.centerIn: parent
            text: parent.readyCountNumber
            font.pixelSize: 40

        }

        Timer{
            id: id_readyCountChangeTimer
            interval: 1000
            onTriggered: {
                if (1 == parent.readyCountNumber)
                {
                    parent.visible = false
                    parent.countOver()
                }
                else
                {
                    parent.readyCountNumber--
                }
            }
        }
    }

    PopupLayer {
        id: id_pausePopup
        objectName: "id_pausePopup"
        signal clickedResumed()
        signal clickedSettingButton()
        visible: false

        HButton{
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width /3
            height: parent.height /6
            anchors.left: parent.left
            anchors.leftMargin: parent.width/12
            strButtonText: ""
            visibleRectangle: false
            onClicked: parent.clickedResumed()

            Image {
                source: "qrc:/image/play.png"
            }
        }

        HSettingButton{
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width /3
            height: parent.height /6
            anchors.right: parent.right
            anchors.rightMargin: parent.width/12
            onClicked: parent.clickedSettingButton()
        }
    }
}


