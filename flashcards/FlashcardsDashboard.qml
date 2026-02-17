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
        width: parent.width - drawer.width
        height: parent.height - header.width
        color: "#2b2b2e"

        anchors {
            left: drawer.right
            top: header.bottom
        }


        GridView {
            anchors.fill: parent
            anchors.leftMargin: 15
            anchors.topMargin: 15

            cellWidth: 220
            cellHeight: 220

            model: TileSetModel {
                id: tileSetModel
            }
            delegate: TileSet{
                title: name
                value: count
                isSpecial: isAdd
                onClicked: console.log("Tile clicked: learn mode");
                onEditClicked: {
                    stackView.push("../flashcards/SetCreator.qml", {
                        setName: name,
                        setId: id
                    })
                }
            }


            Component.onCompleted: {
                firebaseController.loadSets();
            }
        }


        Connections {
            target: firebaseController
            function onSetsLoaded(data) {
                tileSetModel.loadData(data)
            }
        }

    }
}
