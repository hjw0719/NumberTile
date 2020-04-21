import QtQuick 2.0

Item {
    id: id_gauge
    property int maxGauge: 10000;
    property real currentPercent: 1

    property var score : 0
    property var combo : 0
    signal timeOver()


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
