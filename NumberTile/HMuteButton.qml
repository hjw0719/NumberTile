import QtQuick 2.0

HButton{
    width : 30
    height : 30

    strButtonText: bMute ? "≠" : "♬"

    signal soundMuteChanged(bool bMute)

    property bool bMute : false

    onClicked: {
        bMute = !bMute
        soundMuteChanged(bMute)
    }
}
