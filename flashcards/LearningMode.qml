import QtQuick 2.15
import QtQuick.Controls.Fusion
import "../components"
import my.models 1.0
import QtQuick.Layouts

Rectangle {
    id: root
    anchors.fill: parent
    color: "#2b2b2e"
    property string appFont: "Josefin Sans"
    property string setId: ""
    property int currentIndex: 0

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
        id: mainRectangle
        width: parent.width - drawer.width
        height: parent.height - header.width
        color: "#2b2b2e"

        anchors {
            left: drawer.right
            top: header.bottom
        }

        Loader {
            id: cardLoader
            anchors.centerIn: parent
            width: parent.width * 0.7
            height: parent.height * 0.6
            sourceComponent: Card {}

            onLoaded: {
                cardLoader.item.nextCard.connect(function() {
                    currentIndex++;
                });
            }
        }

        Row {
            id: buttons
            spacing: 25
            anchors {
                bottom: parent.bottom
                bottomMargin: 30
                horizontalCenter: parent.horizontalCenter
            }

            MyButton {
                customText: "Umiem!"
                btnWidth: 200
                onClicked: {
                    cardLoader.item.playKnowAnimation();
                }
            }

            MyButton {
                customText: "Powtórz"
                btnWidth: 200
                onClicked: {
                    cardLoader.item.playDontKnowAnimation();
                }
            }
        }
    }

    Connections {
        target: firebaseController
        function onCardsLoaded(data) {
            cardModel.loadCards(data)
            currentIndex = 0
            updateCard()
        }
    }

    Component.onCompleted: {
        firebaseController.loadCards(setId);
    }

    CardModel {
        id: cardModel
    }

    function updateCard() {
        if (!cardLoader.item) return
        if (cardModel.rowCount() <= 0) {
            cardLoader.item.frontText = ""
            cardLoader.item.backText = ""
            return
        }

        const card = cardModel.get(currentIndex)
        cardLoader.item.frontText = card.front
        cardLoader.item.backText = card.back
    }

    Connections {
        target: cardModel
        function onModelReset() { updateCard(); }
        function onDataChanged() { updateCard(); }
    }

    onCurrentIndexChanged: updateCard()
}
