import QtQuick 2.15
import QtQuick.Controls.Fusion
import "../../components"
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
        width: parent.width
        height: parent.height - header.width
        color: "#2b2b2e"

        anchors {
            left: parent.left
            top: header.bottom
        }


        GridView {
            id: grid
            anchors.fill: parent
            anchors.topMargin: 15

            property int columns: Math.floor(width / cellWidth)
            property int gridWidth: columns * cellWidth
            leftMargin: Math.max(0, ((width - gridWidth) / 2) + 10 )

            cellWidth: 170
            cellHeight: 170

            model: TileSetModel {
                id: tileSetModel
            }
            delegate: TileSet{
                title: name
                value: count
                isSpecial: isAdd
                onClicked: stackView.push("../../flashcards/LearningMode.qml",{
                                setId: id
                            })
                onEditClicked: {
                    stackView.push("../../flashcards/SetCreator.qml", {
                        setName: name,
                        setId: id
                    })
                }
                onDeleteClicked: {
                    deleteDialog.disabled = true
                    deleteDialog.visible = true
                    deleteDialog.setId = id
                    deleteDialog.setName = name
                    sleepTimer.start();
                }
            }


            Component.onCompleted: {
                firebaseController.loadSets();
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
            function onSetsLoaded(data) {
                tileSetModel.loadData(data)
            }
        }

        Connections {
            target: firebaseController
            function onDeleteSetCompleted() {
                firebaseController.loadSets();
                deleteDialog.visible = false
            }
        }

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
