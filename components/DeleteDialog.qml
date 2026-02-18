import QtQuick 2.15

Item {
    id: root
    width: 320
    height: 140

    property string setId: ""
    property string setName: ""
    property string appFont: "Josefin Sans"
    property color fontWhiteColor: "#f9fafc"
    property color backgroundColor: "#212224"
    property bool disabled: true

    signal noClicked();
    signal yesClicked();

    Rectangle {
        id: box
        width: root.width
        height: root.height
        color: backgroundColor
        radius: 25

        Text {
            text: "Are you sure to delete this set?"
            font.pixelSize: 16
            font.family: appFont
            color: fontWhiteColor
            anchors {
                top: parent.top
                left: parent.left
                topMargin: 16
                leftMargin: 16
            }
        }

        Text {
            text: setName
            anchors.centerIn: parent
            font.pixelSize: 16
            font.family: appFont
            color: fontWhiteColor
        }

        MyButton {
            isIcon: false
            customText: "No"
            btnWidth: 120

            anchors {
                left: parent.left
                bottom: parent.bottom
                leftMargin: 16
                bottomMargin: 16
            }

            onClicked: root.noClicked();
        }

        MyButton {
            isIcon: false
            customText: "Yes"
            btnWidth: 120
            isDisabled: disabled

            normalColor: "#D32F2F"
            hoverColor: "#E04848"
            pressedColor: "#B71C1C"
            textColor: fontWhiteColor

            anchors {
                right: parent.right
                bottom: parent.bottom
                rightMargin: 16
                bottomMargin: 16
            }

            onClicked: root.yesClicked();
        }
    }
}
