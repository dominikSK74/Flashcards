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
    property int cardCount: 0
    property int learned: 0
    property int needRepeated: 0
    property color fontWhiteColor: "#f9fafc"
    property color backgroundColor: "#212224"

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

        Item {
            id: infoBar
            width: cardLoader.width
            height: 60
            anchors {
                bottom: cardLoader.top
                bottomMargin: 25
                horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                id: needRepeatedCounter
                height: 30
                width: 140
                border.width: 3
                border.color: "#f39c12"
                radius: 5
                color: backgroundColor

                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }

                Text {
                    font.family: appFont
                    font.pixelSize: 16
                    color: fontWhiteColor
                    text: "Need repeated " + needRepeated
                    anchors.centerIn: parent
                }

                Behavior on opacity {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.OutQuad
                    }
                }
            }

            Text {
                id: doneCounter
                font.family: appFont
                font.pixelSize: 16
                color: fontWhiteColor
                text: currentIndex + 1 + " / " + cardCount;
                anchors.centerIn: parent
            }

            Rectangle {
                id: learnedCounter
                height: 30
                width: 140
                border.width: 3
                border.color: "#27ae60"
                radius: 5
                color: backgroundColor

                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }


                Text {
                    font.family: appFont
                    font.pixelSize: 16
                    color: fontWhiteColor
                    text: "Learned " + learned
                    anchors.centerIn: parent
                }

                Behavior on opacity {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.OutQuad
                    }
                }
            }
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

                cardLoader.item.viewSummary.connect(function() {
                    summaryAnimation.start();
                    needRepeatedButton.opacity = 0;
                    learnedButton.opacity = 0;
                    needRepeatedCounter.opacity = 0;
                    learnedCounter.opacity = 0;
                    doneCounter.opacity = 0;
                });
            }
        }

        Rectangle {
            id: summary
            color: "#212224"
            anchors.centerIn: parent
            width: parent.width * 0.7
            height: parent.height * 0.6
            visible: false
            border.color: "#212224"
            radius: 25
            border.width: 5

            Text {
                text: "Summary"
                color: fontWhiteColor
                font.pixelSize: 24
                font.family: appFont
                anchors {
                    top: parent.top
                    topMargin: 25
                    horizontalCenter: parent.horizontalCenter
                }
            }

            Column {
                anchors.centerIn: parent
                spacing: 15

                Text {
                    color: fontWhiteColor
                    font.pixelSize: 18
                    font.family: appFont
                    text: learned + "/" + cardModel.rowCount()
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                MyButton {
                    isIcon: false
                    customText: "Repeat " + needRepeated + " flashcards"
                    width: 300
                    visible: (needRepeated > 0) ? true : false
                    onClicked: {
                        cardModel.loadList(needRepeatedCardModel.getList());
                        needRepeatedCardModel.clearList();
                        resetCards();
                    }
                }

                MyButton {
                    isIcon: false
                    width: 300
                    customText: "Repeat all flashcards"
                    onClicked: {
                        needRepeatedCardModel.clearList();
                        resetCards();
                    }
                }

                MyButton {
                    isIcon: false
                    customText: "Back to dashboard"
                    width: 300
                    onClicked: {
                        stackView.push("FlashcardsDashboard.qml");
                    }
                }
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
                id: needRepeatedButton
                iconsrc: "qrc:assets/close-icon.svg"
                onClicked: {
                    var front = cardModel.get(currentIndex).front
                    var back = cardModel.get(currentIndex).back
                    needRepeatedCardModel.addCard(front, back)
                    needRepeated++

                    if(cardModel.rowCount() === currentIndex + 1){
                        cardLoader.item.playDontKnowEnd();
                    }else {
                        cardLoader.item.playDontKnowAnimation();
                    }
                }

                Behavior on opacity {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.OutQuad
                    }
                }
            }

            MyButton {
                id: learnedButton
                iconsrc: "qrc:assets/check-icon.svg"
                onClicked: {
                    learned++

                    if(cardModel.rowCount() === currentIndex + 1){
                        cardLoader.item.playKnowEnd();
                    }else {
                        cardLoader.item.playKnowAnimation();
                    }
                }

                Behavior on opacity {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.OutQuad
                    }
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
            cardCount = cardModel.rowCount();
        }
    }

    Component.onCompleted: {
        firebaseController.loadCards(setId);
    }

    CardModel {
        id: cardModel
    }

    CardModel {
        id: needRepeatedCardModel
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

    SequentialAnimation {
        id: summaryAnimation
        running: false

        ScriptAction { script: summary.x = summary.x - root.width }
        ScriptAction { script: summary.border.color = "#9f86ff"}
        ScriptAction { script: summary.scale = 1.5}
        ScriptAction { script: summary.rotation = -15 }
        ScriptAction { script: summary.opacity = 0.5 }
        ScriptAction { script: summary.visible = true }

        ParallelAnimation {
            PropertyAnimation { target: summary; property: "x"; to: summary.x + root.width; duration: 260; easing.type: Easing.InQuad }
            PropertyAnimation { target: summary; property: "opacity"; to: 1; duration: 260; easing.type: Easing.InQuad }
        }

        ParallelAnimation {
            PropertyAnimation { target: summary; property: "scale"; to: 1; duration: 180; easing.type: Easing.OutQuad }
            PropertyAnimation { target: summary; property: "rotation"; to: 0; duration: 180; easing.type: Easing.OutQuad }
        }

        PropertyAnimation { target: summary; property: "border.color"; to: "#212224"; duration: 180; easing.type: Easing.OutQuad }
    }

    function resetCards() {
        learned = 0;
        needRepeated = 0;
        cardLoader.item.showCard();
        needRepeatedButton.opacity = 1;
        learnedButton.opacity = 1;
        needRepeatedCounter.opacity = 1;
        learnedCounter.opacity = 1;
        summary.visible = false;
        currentIndex = 0;
        cardCount = cardModel.rowCount();
        doneCounter.opacity = 1;
    }
}
