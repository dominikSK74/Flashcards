import QtQuick 2.15

Item {
    id: root
    property int cardWidth: 400
    width: cardWidth
    implicitHeight: row.implicitHeight

    signal removeClicked()

    Row {
        spacing: 10
        Row {
            id: row
            spacing: 50

            MyTextArea {
                label: "Front card"
                inputWidth: (cardWidth - 100) / 2

                text: model.front

                onTextChanged: {
                    model.front = text
                }

            }

            MyTextArea {
                label: "Back card"
                inputWidth: (cardWidth - 100) / 2

                text: model.back

                onTextChanged: {
                    model.back = text
                }

            }
        }

        MyButton {
            iconsrc: "qrc:assets/remove-icon.svg"
            onClicked: root.removeClicked();
            btnWidth: 38
            btnHeight: 38
            anchors.bottom: parent.bottom
        }
    }



}
