import QtQuick 2.0
import QtQuick.Controls 1.4

Page {

    Button{
        id : id_backButton
        objectName: "id_backButton"

        anchors.top: parent.top
        width : 60
        height : 60
        anchors.right: parent.right

        signal backButtonClicked()

        onClicked: {
            backButtonClicked()
        }
    }

    Rectangle{
        width : parent.width/2
        height : parent.height/2

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
        }

        Slider{
            id: id_bgmSlider
            objectName: "id_bgmSlider"

            anchors.top: id_bgmText.bottom

            width : parent.width - 10
            anchors.horizontalCenter: parent.horizontalCenter

            maximumValue: 100
            minimumValue: 1
            stepSize: 1
            signal soundValueChanged(int value)
            onValueChanged: {
                soundValueChanged(value)
            }
        }

        Text {
            id: id_effectText
            text: qsTr("Effect")

            width : parent.width/3
            height : 50

            anchors.top: id_bgmText.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }

        Slider{
            id: id_effectSlider
            objectName: "id_effectSlider"

            anchors.top: id_effectText.bottom

            width : parent.width - 10
            anchors.horizontalCenter: parent.horizontalCenter

            maximumValue: 100
            minimumValue: 1
            stepSize: 1

            signal soundValueChanged(int value)
            onValueChanged: {
                soundValueChanged(value)
            }
        }
    }


}
