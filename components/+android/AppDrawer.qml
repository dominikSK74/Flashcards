import QtQuick 2.15
import QtQuick.Controls.Fusion
import "../"
import Qt5Compat.GraphicalEffects

Drawer {
    id: root
    width: parent.width * 0.6
    height: parent.height - 50
    edge: Qt.LeftEdge
    y: 50

    property color backgroundColor: "#212224"
    property string appFont: "Josefin Sans"
    property color fontWhiteColor: "#f9fafc"

    Rectangle {
        anchors.fill: parent
        anchors.left: parent.left

        color: backgroundColor

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            anchors.top: parent.top
            anchors.topMargin: 25

            Label {
                text: "Flashcards app"
                font.family: appFont
                font.pixelSize: 24
                color: fontWhiteColor
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            DrawerButton {
                customText: "Dashboard"
                btnWidth: root.width - 20
                onClicked: {
                    stackView.push("../dashboard/dashboard.qml");
                    root.close();
                }
            }

            DrawerButton {
                customText: "Flashcards"
                btnWidth: root.width - 20
                onClicked: {
                    stackView.push("../flashcards/FlashcardsDashboard.qml");
                    root.close();
                }
            }

            DrawerButton {
                customText: "Quiz"
                btnWidth: root.width - 20
            }
        }

        MyButton {
            btnWidth: root.width - 20
            customText: "Logout"
            iconsrc: "qrc:assets/logout-icon.svg"
            normalColor: "#D32F2F"
            hoverColor: "#E04848"
            pressedColor: "#B71C1C"
            textColor: fontWhiteColor
            anchors.bottom: footer.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 10
            onClicked: loginController.logout();
        }

        Rectangle {
            id: footer
            width: parent.width
            height: 60
            color: "#131314"
            anchors.bottom: parent.bottom

            Row{
                spacing: 5
                anchors.fill: parent

                Item {
                    width: 70
                    height: 70
                    anchors.verticalCenter: parent.verticalCenter

                    Image {
                        id: img
                        source: session.avatarUrl
                        width: parent.width/2
                        height: width
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectCrop
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: mask
                        }
                    }

                    Rectangle {
                        id: mask
                        width: parent.width/2
                        height: width
                        radius: width/2
                        visible: false
                    }
                }


                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: session.username
                    font.family: appFont
                    font.pixelSize: 16
                    color: fontWhiteColor
                    font.bold: true
                }
            }
        }
    }
}
