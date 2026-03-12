import QtQuick 2.15
import QtQuick.Controls.Fusion
import "../components"
import my.models 1.0

Rectangle {
    anchors.fill: parent
    color: "#2b2b2e"
    property string appFont: "Josefin Sans"

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


        ListView {
            anchors.fill: parent
            anchors.leftMargin: 15
            anchors.topMargin: 15
            spacing: 20

            model: QuizModel {
                id: quizModel
            }
            delegate: QuizTile {
                title: name
                value: count
                isSpecial: isAdd

                onClicked: {
                    console.log("QUIZ")
                }
            }


            Component.onCompleted: {
                firebaseController.loadQuizzes();
            }
        }

        DeleteDialog {
            id: deleteDialog
            visible: false
            z: 1
            anchors.centerIn: parent

            onYesClicked: firebaseController.deleteSet(setId);
            onNoClicked: deleteDialog.visible = false
        }

        Connections {
            target: firebaseController
            function onQuizzesLoaded(data) {
                quizModel.loadData(data)
            }
        }

        // Connections {
        //     target: firebaseController
        //     function onDeleteSetCompleted() {
        //         firebaseController.loadSets();
        //         deleteDialog.visible = false
        //     }
        // }

        Timer {
            id: sleepTimer
            interval: 3000
            repeat: false
            onTriggered: {
                deleteDialog.disabled = false;
            }
        }
    }
}
