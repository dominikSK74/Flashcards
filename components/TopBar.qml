import QtQuick 2.15

Item {
    width: parent.width
    height: 20
    Rectangle {
        anchors.fill: parent
        color: "red"


        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton

            property point clickPos

            onPressed: clickPos = Qt.point(mouse.x, mouse.y)

            onPositionChanged: {
                window.x += mouse.x - clickPos.x
                window.y += mouse.y - clickPos.y
            }
        }

    }
}
