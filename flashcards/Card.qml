import QtQuick 2.15

Item {
    id: root
    width: Math.min(400, parent.width - 30)
    height: Math.min(550, parent.height - 30)

    property string frontText: "Front"
    property string backText: "Back"

    property color backgroundColor: "#212224"
    property string appFont: "Josefin Sans"
    property color fontWhiteColor: "#f9fafc"
    property int flipDuration: 600

    signal nextCard();

    Flipable {
        id: flipable
        anchors.fill: parent

        property bool flipped: false

        front: Rectangle {
            id: cardRoot
            anchors.fill: parent
            color: backgroundColor
            border.color: backgroundColor
            radius: 25
            border.width: 5
            Text {
                font.pixelSize: 20
                color: fontWhiteColor
                font.family: appFont
                anchors.centerIn: parent
                text: frontText
            }
        }

        back: Rectangle {
            anchors.fill: parent
            color: backgroundColor
            radius: 25
            Text {
                font.pixelSize: 20
                color: fontWhiteColor
                font.family: appFont
                anchors.centerIn: parent
                text: backText
            }
        }

        transform: Rotation {
            id: rotation
            origin.x: flipable.width / 2
            origin.y: flipable.height / 2
            axis.x: 0; axis.y: 1; axis.z: 0
            angle: 0
        }

        states:[
            State {
                name: "back"
                when: flipable.flipped
                PropertyChanges {
                    target: rotation
                    angle: 180
                }
            }
        ]

        transitions: [
            Transition {
                NumberAnimation {
                    target: rotation
                    property: "angle"
                    duration: flipDuration
                    easing.type: Easing.InOutQuad
                }
            }
        ]

        MouseArea {
            anchors.fill: parent

            onClicked: {
                flipable.flipped = !flipable.flipped
            }
        }
    }

    SequentialAnimation {
        id: slideOutRightDontKnow
        running: false

        PropertyAnimation { target: cardRoot; property: "border.color"; to: "#27ae60"; duration: 120 }
        ParallelAnimation {
            PropertyAnimation { target: cardRoot; property: "scale"; to: 1.08; duration: 180; easing.type: Easing.OutQuad }
            PropertyAnimation { target: cardRoot; property: "rotation"; to: 15; duration: 180; easing.type: Easing.OutQuad }
        }
        ParallelAnimation {
            PropertyAnimation { target: cardRoot; property: "x"; to: parent.width + cardRoot.width; duration: 260; easing.type: Easing.InQuad }
            PropertyAnimation { target: cardRoot; property: "opacity"; to: 0; duration: 260; easing.type: Easing.InQuad }
        }

        onStopped: {
            nextCard();
            slideInFromLeftDontKnow.start();
        }
    }

    SequentialAnimation {
        id: slideInFromLeftDontKnow
        running: false

        PropertyAnimation { target: cardRoot; property: "x"; to: -cardRoot.width; duration: 0 }
        PropertyAnimation { target: cardRoot; property: "opacity"; to: 0; duration: 0 }
        ParallelAnimation {
            PropertyAnimation { target: cardRoot; property: "x"; to: 0; duration: 260; easing.type: Easing.OutQuad }
            PropertyAnimation { target: cardRoot; property: "opacity"; to: 1; duration: 260; easing.type: Easing.OutQuad }
        }
        ParallelAnimation {
            PropertyAnimation { target: cardRoot; property: "scale"; to: 1.0; duration: 140; easing.type: Easing.OutQuad }
            PropertyAnimation { target: cardRoot; property: "rotation"; to: 0; duration: 140; easing.type: Easing.OutQuad }
        }
        PropertyAnimation { target: cardRoot; property: "border.color"; to: "#212224"; duration: 120 }
    }

    SequentialAnimation {
        id: slideOutLeftKnow
        running: false

        PropertyAnimation { target: cardRoot; property: "border.color"; to: "#f39c12"; duration: 120 }
        ParallelAnimation {
            PropertyAnimation { target: cardRoot; property: "scale"; to: 1.08; duration: 180; easing.type: Easing.OutQuad }
            PropertyAnimation { target: cardRoot; property: "rotation"; to: -15; duration: 180; easing.type: Easing.OutQuad }
        }
        ParallelAnimation {
            PropertyAnimation { target: cardRoot; property: "x"; to: -cardRoot.width - parent.width * 0.1; duration: 260; easing.type: Easing.InQuad }
            PropertyAnimation { target: cardRoot; property: "opacity"; to: 0; duration: 260; easing.type: Easing.InQuad }
        }

        onStopped: {
            nextCard();
            slideInFromRightKnow.start();
        }
    }

    SequentialAnimation {
        id: slideInFromRightKnow
        running: false

        PropertyAnimation { target: cardRoot; property: "x"; to: parent.width + cardRoot.width; duration: 0 }
        PropertyAnimation { target: cardRoot; property: "opacity"; to: 0; duration: 0 }
        ParallelAnimation {
            PropertyAnimation { target: cardRoot; property: "x"; to: 0; duration: 260; easing.type: Easing.OutQuad }
            PropertyAnimation { target: cardRoot; property: "opacity"; to: 1; duration: 260; easing.type: Easing.OutQuad }
        }
        ParallelAnimation {
            PropertyAnimation { target: cardRoot; property: "scale"; to: 1.0; duration: 140; easing.type: Easing.OutQuad }
            PropertyAnimation { target: cardRoot; property: "rotation"; to: 0; duration: 140; easing.type: Easing.OutQuad }
        }
        PropertyAnimation { target: cardRoot; property: "border.color"; to: "#212224"; duration: 120 }
    }

    SequentialAnimation {
        id: flipBackThenDontKnow
        running: false
        ScriptAction { script: flipable.flipped = false }
        PauseAnimation { duration: flipDuration }
        ScriptAction { script: slideOutRightDontKnow.start() }
    }

    SequentialAnimation {
        id: flipBackThenKnow
        running: false
        ScriptAction { script: flipable.flipped = false }
        PauseAnimation { duration: flipDuration }
        ScriptAction { script: slideOutLeftKnow.start() }
    }

    function playKnowAnimation() {
        if (flipable.flipped) {
            flipBackThenDontKnow.start()
        } else {
            slideOutRightDontKnow.start()
        }
    }

    function playDontKnowAnimation() {
        if (flipable.flipped) {
            flipBackThenKnow.start()
        } else {
            slideOutLeftKnow.start()
        }
    }
}
