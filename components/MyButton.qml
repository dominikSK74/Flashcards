import QtQuick 2.15

Rectangle {
    id: root
    width: btnWidth
    height: btnHeight
    radius: 6
    color: controlColor

    property string customFont: ""
    property string iconsrc: ""
    property string customText: ""
    property color normalColor: "#9f86ff"
    property color hoverColor: "#a78fff"
    property color pressedColor: "#9380d8"
    property color textColor: "#1a0056"
    property int btnWidth: 45
    property int btnHeight: 45

    readonly property color controlColor: mouseArea.pressed ? pressedColor : mouseArea.containsMouse ? hoverColor: normalColor

    signal clicked();
    Row {
        anchors.centerIn: parent
        spacing: 10
        Image {
            source: iconsrc
            fillMode: Image.PreserveAspectFit
            width: 32
            height: 32
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: customText
            color: textColor
            font.pixelSize: 22
            font.family: customFont
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            root.clicked()
        }
    }
}
