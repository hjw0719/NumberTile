import QtQuick 2.0
import QtQuick.Controls 1.4

Page {

    HButton{
        id : id_backButton
        objectName: "id_backButton"

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        width : 60
        height : 60

        strButtonText: "<"

        signal backButtonClicked()

        onClicked: {
            backButtonClicked()
        }
    }

    Item
    {
        width : parent.width
        height : parent.height - id_backButton.height - 5
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        Rectangle{
            width : parent.width/4 * 3
            height : parent.height/6 * 5

            readonly property real margin: width / 10

            anchors.centerIn: parent
            color : "dark red"

            Text {
                id: id_bgmText
                text: qsTr("BGM")

                width : parent.width/3
                height : 50

                anchors.top: parent.top
                anchors.topMargin: parent.margin
                anchors.left: parent.left
                anchors.leftMargin: parent.margin

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft

                font.pixelSize: 30
            }

            Slider{
                id: id_bgmSlider
                objectName: "id_bgmSlider"

                anchors.top: id_bgmText.bottom
                anchors.left: parent.left

                width : parent.margin * 7

                enabled: !id_BGMMuteButton.bMute

                maximumValue: 100
                minimumValue: 1
                stepSize: 1

                updateValueWhileDragging : false

                signal soundValueChanged(int value)
                onValueChanged: {
                    soundValueChanged(value)
                }
            }

            HMuteButton{
                id : id_BGMMuteButton
                objectName: "id_BGMMuteButton"

                width : parent.margin * 2
                height : width

                anchors.right: parent.right
                anchors.rightMargin: parent.margin

                anchors.verticalCenter: id_bgmSlider.verticalCenter
            }

            Text {
                id: id_effectText
                text: qsTr("Effect")

                width : parent.width/3
                height : 50

                anchors.top: id_BGMMuteButton.bottom
                anchors.topMargin: parent.margin
                anchors.left: parent.left
                anchors.leftMargin: parent.margin

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft

                font.pixelSize: 30
            }

            Slider{
                id: id_effectSlider
                objectName: "id_effectSlider"

                anchors.top: id_effectText.bottom
                anchors.left: parent.left

                width : parent.margin * 7

                enabled: !id_effectMuteButton.bMute

                maximumValue: 100
                minimumValue: 1
                stepSize: 1

                updateValueWhileDragging : false

                signal soundValueChanged(int value)
                onValueChanged: {
                    soundValueChanged(value)
                }
            }

            HMuteButton{
                id : id_effectMuteButton
                objectName: "id_effectMuteButton"

                width : parent.margin*2
                height : width
                anchors.right: parent.right
                anchors.rightMargin: parent.margin

                anchors.verticalCenter: id_effectSlider.verticalCenter
            }
        }
    }



}
