import QtQuick 2.12
import QtGraphicalEffects 1.12
Item {
    id: id_gauge
    property int maxGauge: 10000;
    property real currentPercent: 1

    property var score : 0
    property var combo : 0
    signal timeOver()


    Rectangle{
        id: id_BG
//        color: "red"
        anchors.fill: parent
//        gradient:
    }


    Item{
        id: id_gage
        anchors.left: id_BG.left
        width: currentPercent * parent.width
        height: parent.height
        clip: true
        LinearGradient {
            id: id_gradient
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(id_gauge.width, 0)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#58d3f7" }
                GradientStop { position: 1.0; color: "green" }
            }
            visible: true
        }

//        DropShadow {
//            anchors.fill: id_gradient
//            radius: 8.0
//            samples: 16
//            horizontalOffset: -3
//            verticalOffset: 3
//            color: "#80000000"
//            source: id_gradient
//        }

    }

//    Rectangle{
//        id: id_gage
//        anchors.left: id_BG.left
//        width: currentPercent * parent.width
//        height: parent.height
//        color: "blue"
//    }

    PropertyAnimation{
        id: id_animation
        target: id_gauge
        properties: "currentPercent"
        to: 0
        onRunningChanged: {
            if (!running && 0 === currentPercent)
            {
                timeOver()
            }
        }
    }

    function setRemainGauge(remainGauge)
    {
        id_animation.stop()
        currentPercent = remainGauge / maxGauge
        id_animation.duration = remainGauge
        id_animation.from = currentPercent
    }

    function timerStart()
    {
        if (id_animation.running)
        {
            id_animation.resume()
        }
        else
        {
            id_animation.start()
        }
    }

    function timerResumed()
    {
        id_animation.resume()
    }

    function timerPaused()
    {
        // pause 는 러닝상태를 바꿀수 없다.
        id_animation.pause()
    }

    function timerStop()
    {
        id_animation.stop()
        timeOver()
    }

    function getRemainingTime()
    {
        console.log(currentPercent)
        return maxGauge * currentPercent
    }

    function getIsTimerRunning()
    {
        console.log(id_animation.running)
        return id_animation.running && !id_animation.paused;
    }
}
