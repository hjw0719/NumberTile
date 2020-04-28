import QtQuick 2.0

Rectangle {

//    property string mainColor : bFever ? "red" : "#000066"

    Connections {
        target: id_mainGamePage
        onBFeverChanged:{
            if (bFever)
            {
                id_colorAnimation.start()
            }
        }
    }

    gradient: Gradient {
        GradientStop {
            id: firstGradient
            position: 0.0;
            color: "#000066"
        }



        GradientStop { position: 1.0; color: "#cc99cc" }
    }

    ColorAnimation {
        id: id_colorAnimation
        target: firstGradient
        property: "color"
        from: "red"
        to: "#000066"
        duration: 5000
    }
}
