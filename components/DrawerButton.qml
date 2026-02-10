import QtQuick 2.15

Rectangle {
    id: root
    width: btnWidth
    height: btnHeight
    radius: 6
    color: controlColor

    property string customFont: "Josefin Sans"
    property string customText: ""
    property color normalColor: "#212224"
    property color hoverColor: "#801a0056"
    property color pressedColor: "#9380d8"
    property color textColor: "#9f86ff"
    property int btnWidth: 300
    property int btnHeight: 45

    readonly property color controlColor: mouseArea.pressed ? pressedColor : mouseArea.containsMouse ? hoverColor: normalColor

    signal clicked();

    Text {
        text: customText
        color: textColor
        font.pixelSize: 22
        font.family: customFont
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
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
