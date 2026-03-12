import QtQuick 2.15

Item {
    id:root
    property string title: "Empty"
    property int value: 0
    property color backgroundColor: "#212224"
    property string appFont: "Josefin Sans"
    property color fontWhiteColor: "#f9fafc"
    property bool isSpecial: false
    property color normalColor: "#9f86ff"
    property color darkTextColor: "#1a0056"
    property color hoverColor: "#a78fff"
    property color pressedColor: "#9380d8"

    readonly property color specialColor: mouseArea.pressed ? pressedColor : mouseArea.containsMouse ? hoverColor: normalColor
    readonly property color controlColor: mouseArea1.pressed ? "#3800b8" : mouseArea1.containsMouse ? darkTextColor: backgroundColor

    width: parent.width - 40
    height: 70

    signal clicked();

    Rectangle {
        id: box
        anchors.fill:parent
        radius: 10

        color: isSpecial ? specialColor : controlColor

        Item {
            z:1
            anchors.fill: parent
            visible: !isSpecial
            Text {
                font.family: appFont
                font.pixelSize: 20
                color: fontWhiteColor
                text: title
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 15
                }
            }

            Text {
                font.family: appFont
                font.pixelSize: 20
                color: fontWhiteColor
                text: value
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: 15
                }
            }
        }

        Image {
            visible: isSpecial
            source: "qrc:assets/add-icon.svg"

            width: 60
            height: 60
            anchors.centerIn: parent

            sourceSize.width: width
            sourceSize.height: height

            fillMode: Image.PreserveAspectFit
            smooth: true
        }

        MouseArea {
            id: mouseArea
            visible: isSpecial
            anchors.fill: parent
            hoverEnabled: true
            z: 0
            onClicked: {
                // stackView.push("../flashcards/SetCreator.qml")
                console.log("create new quiz")
            }
        }

        MouseArea {
            id: mouseArea1
            visible: !isSpecial
            anchors.fill: parent
            hoverEnabled: true
            z: 0
            onClicked: {
                root.clicked()
            }
        }
    }
}
