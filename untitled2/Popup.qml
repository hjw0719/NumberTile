import QtQuick 2.0

Rectangle {
    property string strDisplayText: ""
    anchors.centerIn: parent
    width: parent.width/2.0
    height: parent.height/2.0

    Text {
        id: name
        text: strDisplayText
        font.pixelSize: 20
        anchors.centerIn: parent
    }
}
