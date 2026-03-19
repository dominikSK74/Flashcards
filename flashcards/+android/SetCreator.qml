import QtQuick 2.15
import QtQuick.Controls.Fusion
import "../../components"
import my.models 1.0
import QtQuick.Dialogs

Rectangle {
    anchors.fill: parent
    color: "#2b2b2e"
    property string appFont: "Josefin Sans"

    property string setName: ""
    property string setId: ""
    property var jsonData: ({})

    Component.onCompleted: {
        if (setId === "") {
            listview.model.addEmptyCard();
        } else {
            firebaseController.loadCards(setId);
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
        width: parent.width
        height: parent.height - header.height
        color: "#2b2b2e"

        anchors {
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
                right: parent.right
                topMargin: 15
                leftMargin: 20
                rightMargin: 20
            }

            CustomInput {
                id: setNameInput
                inputWidth: Math.min((parent.width / 2) - 20, 350)
                label: "Set name"
                text: setName
            }

            MyButton {
                id: saveBtn
                isIcon: false
                customText: "Save set"
                btnWidth: 150

                anchors {
                    right: headBox.right
                    rightMargin: 15
                    verticalCenter: parent.verticalCenter
                }

                onClicked: {
                    listview.model.saveSet(setId, setNameInput.text, firebaseController, jsonData);
                }
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

            model: CardModel {
                id: cardModel
            }
            delegate: CardInput {
                cardWidth: ListView.view.width
                onRemoveClicked: {
                    cardModel.removeCard(index);
                }
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
            onClicked: listview.model.addEmptyCard();

        }

        Alert {
            id: alert
            visible: false
            type: "warning"
            message: ""
            onClicked: {
                alert.visible = false
                closeAlertTimer.restart();
            }
        }
    }

    Connections {
        target: firebaseController
        function onAddingSetCompleted(data) {
            stackView.push("FlashcardsDashboard.qml");
        }
    }

    Connections {
        target: firebaseController
        function onCardsLoaded(data) {
            cardModel.loadCards(data);
            jsonData = data;
        }
    }

    Connections {
        target: firebaseController
        function onLoadCardsFromNextPage(data) {
            cardModel.addCardsFromNextPage(data)
            jsonData = cardModel.mergeJsonDocuments(jsonData, data)
        }
    }

    Timer {
        id: closeAlertTimer
        interval: 5000
        repeat: false
        onTriggered: {
            alert.visible = false
        }
    }

    Connections {
        target: cardModel
        function onSendAlert(type, message) {
            alert.type = type
            alert.message = message
            alert.visible = true
            closeAlertTimer.start();
        }
    }
}
