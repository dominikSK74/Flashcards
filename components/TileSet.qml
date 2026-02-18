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
    signal clicked();
    signal editClicked();
    signal deleteClicked();

    readonly property color specialColor: mouseArea.pressed ? pressedColor : mouseArea.containsMouse ? hoverColor: normalColor
    readonly property color controlColor: mouseArea1.pressed ? "#3800b8" : mouseArea1.containsMouse ? darkTextColor: backgroundColor


    width: 200
    height: 200

    Rectangle {
        id: box
        anchors.fill:parent
        radius: 25

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
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
            }

            Text {
                font.family: appFont
                font.pixelSize: 32
                color: fontWhiteColor
                text: value
                anchors.centerIn: parent
            }

            Row {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                spacing: 40
                anchors.horizontalCenter: parent.horizontalCenter


                MyButton {
                    iconsrc: "qrc:assets/edit-icon.svg"
                    onClicked: root.editClicked();
                }

                MyButton {
                    iconsrc: "qrc:assets/delete-icon.svg"
                    onClicked: root.deleteClicked();
                }
            }

        }

        Image {
            visible: isSpecial
            source: "qrc:assets/add-icon.svg"

            width: 96
            height: 96
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
                stackView.push("../flashcards/SetCreator.qml")
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
