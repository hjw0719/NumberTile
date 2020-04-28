import QtQuick 2.0
import HTile 1.0
import HEnum 1.0
import QtQuick.Particles 2.0
HTile {
    id : id_tile

    property alias mouseArea : id_mouseArea;

    Rectangle {
        id : id_background
        anchors.fill: parent
        color: HEnum.E_TILE_STATUS_FEVER === id_tile.status ? "white"
                                                            : "#00000000"
        //                                                                    : HEnum.E_TILE_STATUS_OCCUPY === id_tile.status ? "#00000000"
        //                                                                                                                    : "white"
        Text {
            id: id_numberText
            anchors.centerIn: parent
            text: HEnum.E_TILE_STATUS_OCCUPY === id_tile.status ? id_tile.number : ""
            font.pixelSize: 40
            color: "white"
            font.bold: true
        }
        border.color: "white"
        border.width: 5

        scale: id_mouseArea.pressed ? 0.8 : 1

        radius: 20
    }

    MouseArea {
        id : id_mouseArea
        anchors.fill: parent
    }

//    ParticleSystem{
//        id: id_explodeAnimation
//        anchors.fill: parent
//        Emitter {
//            id: heartEmitter
//            enabled: false
//            maximumEmitted: 6000
//            group: "success"
//            emitRate: 1000
//            size: 16
//            endSize: 8
//            velocity: AngleDirection {angleVariation: 180; magnitudeVariation: 180;}
//            lifeSpan: 300
//        }

//        ImageParticle {
//            groups: ["success"]
//            color: "white"
//            z: 1
//            source: "qrc:/image/star.png"
//            alpha: 0.4
//            autoRotation: true
//        }
//    }
}
