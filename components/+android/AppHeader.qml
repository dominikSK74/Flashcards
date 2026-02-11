import QtQuick 2.15
import "../"

Rectangle {
    width: parent.width
    height: 50

    property string appFont: "Josefin Sans"
    property color fontWhiteColor: "#f9fafc"
    property color primaryColor: "#9f86ff"
    property string textMsg: "Flashcards"
    signal menuClicked();

    color: primaryColor


    Item {
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: parent.height

        MyButton {
            id: menuButton
            iconsrc: "qrc:assets/menu-icon.svg"
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.verticalCenter: parent.verticalCenter
            onClicked: menuClicked()
        }

        Text {
            id: title
            text: textMsg
            font.pixelSize: 20
            color: fontWhiteColor
            anchors.centerIn: parent
            font.bold: true
        }
    }


}
