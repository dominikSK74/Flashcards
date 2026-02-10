import QtQuick 2.15
import QtQuick.Controls.Fusion

Drawer {
    width: 350
    edge: Qt.LeftEdge
    y: 45
    height: parent.height - 45


    Rectangle {
        anchors.fill: parent
        color: "red"

        Column {
            spacing: 10

            MyButton {
                customText: "Flashcards"
                btnWidth: 300
            }

            MyButton {
                customText: "Quiz"
                btnWidth: 300
            }
        }
    }
}
