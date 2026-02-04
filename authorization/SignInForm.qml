import QtQuick 2.15
import "../components"

Rectangle {
    anchors.fill: parent
    color: "#2b2b2e"

    property string appFont: "Josefin Sans"

    Column {
        anchors.centerIn: parent
        spacing: 32

        Text {
            text: "Welcome in flashcards app"
            font.family: appFont
            color: "#f9fafc"
            font.pixelSize: 24
        }

        MyButton {
            customText: "Sign in by Google"
            btnWidth: 250
            iconsrc: "qrc:assets/google-logo.svg"
            customFont: appFont
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
