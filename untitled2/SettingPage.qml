import QtQuick 2.0

Page {

    Text {
        id: id_bgmText
        text: qsTr("BGM")

        width : parent.width/4
        height : 50

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        id: id_effectText
        text: qsTr("Effect")

        width : parent.width/4
        height : 50

        anchors.top: id_bgmText.bottom
        anchors.topMargin: 10
        anchors.left: parent.left

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
