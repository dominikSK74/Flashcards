import QtQuick 2.15

Item {
    property int cardWidth: 400
    width: cardWidth
    implicitHeight: row.implicitHeight


    Row {
        id: row
        spacing: 50
        MyTextArea {
            label: "Front card"
            inputWidth: (cardWidth - 50) / 2

            text: model.front

            onTextChanged: {
                model.front = text
            }

        }

        MyTextArea {
            label: "Back card"
            inputWidth: (cardWidth - 50) / 2

            text: model.back

            onTextChanged: {
                model.back = text
            }

        }
    }
}
