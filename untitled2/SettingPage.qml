import QtQuick 2.0
import QtQuick.Controls 1.4

Page {

    HButton{
        id : id_backButton
        objectName: "id_backButton"

        anchors.top: parent.top
        width : 60
        height : 60
        anchors.right: parent.right

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

            anchors.centerIn: parent
            color : "dark red"

            Text {
                id: id_bgmText
                text: qsTr("BGM")

                width : parent.width/3
                height : 50

                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft

                font.pixelSize: 30
            }

            Slider{
                id: id_bgmSlider
                objectName: "id_bgmSlider"

                anchors.top: id_bgmText.bottom

                width : parent.width - 45
                anchors.left: parent.left
                anchors.leftMargin: 5

                enabled: !id_BGMMuteButton.bMute

                maximumValue: 100
                minimumValue: 1
                stepSize: 1
                signal soundValueChanged(int value)
                onValueChanged: {
                    soundValueChanged(value)
                }
            }

            HMuteButton{
                id : id_BGMMuteButton
                objectName: "id_BGMMuteButton"
                anchors.right: parent.right
                anchors.rightMargin: 5

                anchors.verticalCenter: id_bgmSlider.verticalCenter
            }

            Text {
                id: id_effectText
                text: qsTr("Effect")

                width : parent.width/3
                height : 50

                anchors.top: id_bgmText.bottom
                anchors.topMargin: 40
                anchors.left: parent.left
                anchors.leftMargin: 10

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft

                font.pixelSize: 30
            }

            Slider{
                id: id_effectSlider
                objectName: "id_effectSlider"

                anchors.top: id_effectText.bottom

                width : parent.width - 45
                anchors.left: parent.left
                anchors.leftMargin: 5

                enabled: !id_effectMuteButton.bMute

                maximumValue: 100
                minimumValue: 1
                stepSize: 1

                signal soundValueChanged(int value)
                onValueChanged: {
                    soundValueChanged(value)
                }
            }

            HMuteButton{
                id : id_effectMuteButton
                objectName: "id_effectMuteButton"
                anchors.right: parent.right
                anchors.rightMargin: 5

                anchors.verticalCenter: id_effectSlider.verticalCenter
            }
        }
    }



}
