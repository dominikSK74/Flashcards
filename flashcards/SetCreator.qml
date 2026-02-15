import QtQuick 2.15
import QtQuick.Controls.Fusion
import "../components"
import my.models 1.0

Rectangle {
    anchors.fill: parent
    color: "#2b2b2e"
    property string appFont: "Josefin Sans"

    property string setName: ""

    //TODO: W CARD MODEL addEmptyCard, loadDataFromDatabse

    Component.onCompleted: {
        if (setName === "") {
            // CREATE MODE
        } else {
            // EDIT MODE
        }
    }



    AppHeader {
        id: header
        textMsg: "Dashboard"
        onMenuClicked: {
            if (drawer.opened){
                drawer.close();
            }else{
                drawer.open();
            }
        }
    }
    AppDrawer {
        id: drawer
    }

    Rectangle {
        width: parent.width - drawer.width
        height: parent.height - header.width
        color: "#2b2b2e"

        anchors {
            left: drawer.right
            top: header.bottom
        }

        Rectangle {
            id: headBox
            width: parent.width
            color: "transparent"
            height: 80
            anchors {
                top: parent.top
                left: parent.left
                topMargin: 10
                leftMargin: 10
            }


            CustomInput {
                id: setNameInput
                inputWidth: Math.min((parent.width / 2) - 20, 350)
                label: "Set name"
                text: setName
            }
        }

        ListView {
            id: listview

            anchors.top: headBox.bottom
            anchors.topMargin: 25
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: addButton.top
            anchors.margins: 20

            spacing: 20

            model: CardModel {}
            delegate: CardInput {
                frontText: front
                backText: back
                cardWidth: ListView.view.width
            }

        }

        MyButton {
            id: addButton

            anchors {
                right: parent.right
                bottom: parent.bottom
                rightMargin: 25
                bottomMargin: 25
            }

            iconsrc: "qrc:assets/add-icon.svg"

        }
    }
}
