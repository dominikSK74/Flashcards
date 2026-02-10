import QtQuick 2.15
import QtQuick.Controls.Fusion
import "../components"

Rectangle {
    anchors.fill: parent
    color: "#2b2b2e"
    property string appFont: "Josefin Sans"

    AppHeader { id: header }
    AppDrawer { id: drawer }

    Rectangle {
        width: parent.width - drawer.width
        height: parent.height - header.width
        color: "#2b2b2e"

        anchors {
            left: drawer.right
            top: header.bottom
        }

        Column {
            anchors.centerIn: parent

            spacing: 10
            Text {
                text: qsTr("Dashboard")
                font.family: appFont
                color: "#f9fafc"
                font.pixelSize: 24
            }


            MyButton {
                customFont: appFont
                customText: "Czy mam dostęp?"
                btnWidth: 300
                onClicked: firebaseController.testConnection();
            }
        }
    }
}
