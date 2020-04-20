import QtQuick 2.0

Item {
    id: id_gauge
    property int maxGauge: 10000;
    property real currentPercent: 1

    property var score : 0
    property var combo : 0

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
        text: score //id_animation.duration
        anchors.left: parent.left
    }

    Text {
        text: combo // currentPercent
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

//        if (remainGauge === 0)
//            return;

        id_animation.duration = remainGauge
        id_animation.from = currentPercent
        id_animation.start()
    }

}
