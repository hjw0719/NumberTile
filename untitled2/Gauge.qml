import QtQuick 2.0

Item {
    id: id_gauge
    property int maxGauge: 10000;
    property real currentPercent: 1

    Rectangle{
        id: id_BG
        color: "red"
        anchors.fill: parent
    }

    Rectangle{
        id: id_gage
        anchors.left: id_BG.left
        width: currentPercent * parent.width
        height: parent.height
        color: "blue"
    }

    Text {
        text: id_animation.duration
        anchors.left: parent.left
    }

    Text {
        text: currentPercent
        anchors.right: parent.right
    }

    PropertyAnimation{
        id: id_animation
        target: id_gauge
        properties: "currentPercent"
        to: 0
    }

    function setRemainGauge(remainGauge)
    {
        id_animation.stop()
        currentPercent = remainGauge / maxGauge
        id_animation.duration = remainGauge
        id_animation.from = currentPercent
        id_animation.start()
    }

}
