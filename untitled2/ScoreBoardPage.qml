import QtQuick 2.14

Page {
    id : id_scoreBoard

    signal clickedRestartButton()
    signal clickedTitleButton()

    property variant rankModel;

    Rectangle{
        id : id_background
        width : parent.width / 5 * 4
        height : parent.height / 3 * 2

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter

        color : "lightyellow"

        border.color: "purple"
        border.width: 2

        ListView{
            anchors.fill: parent
            delegate : id_delegate
            model : rankModel
            currentIndex: 1
            clip: true
            snapMode: ListView.SnapToItem

            headerPositioning : ListView.OverlayHeader
            header :
                Rectangle {
                    width : id_background.width;
                    height : id_background.height / 10
                    border.color: "purple"
                    border.width: 2
                    color : "lightgreen"
                    z : 2

                    Text{
                        id : id_rank
                        width : parent.width / 4
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        text : "Rank"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text{
                        id : id_name
                        width : parent.width / 4
                        anchors.left: id_rank.right
                        anchors.verticalCenter: parent.verticalCenter
                        text : "Name"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text{
                        id : id_score
                        width : parent.width / 4
                        anchors.left: id_name.right
                        anchors.verticalCenter: parent.verticalCenter
                        text : "Score"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text{
                        id : id_combo
                        width : parent.width / 4
                        anchors.left: id_score.right
                        anchors.verticalCenter: parent.verticalCenter
                        text : "Tile"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

            highlight: Rectangle{
                color: "lightsteelblue"
                radius: 5

                opacity: 0.5
            }
        }
    }


    Component{
        id : id_delegate

        Item{
            width : id_background.width;
            height : id_background.height / 10


            Text{
                id : id_rank
                width : parent.width / 4
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                text : modelData.rank
                font.pixelSize: 15
                horizontalAlignment: Text.AlignHCenter
            }

            Text{
                id : id_name
                width : parent.width / 4
                anchors.left: id_rank.right
                anchors.verticalCenter: parent.verticalCenter
                text : modelData.name
                font.pixelSize: 15
                horizontalAlignment: Text.AlignHCenter
            }

            Text{
                id : id_score
                width : parent.width / 4
                anchors.left: id_name.right
                anchors.verticalCenter: parent.verticalCenter
                text : modelData.score
                font.pixelSize: 15
                horizontalAlignment: Text.AlignHCenter
            }

            Text{
                id : id_combo
                width : parent.width / 4
                anchors.left: id_score.right
                anchors.verticalCenter: parent.verticalCenter
                text : modelData.tile
                font.pixelSize: 15
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    HButton {
        id: id_restartButton
        width: parent.width /3
        height: parent.height / 8
        strButtonText: "Restart"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: parent.width/10
        onClicked:{
            clickedRestartButton()
        }
    }

    HButton {
        id: id_titleButton
        width: parent.width /3
        height: parent.height /8
        strButtonText: "Title"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: parent.width/10
        onClicked:{
            clickedTitleButton()
        }
    }

}
