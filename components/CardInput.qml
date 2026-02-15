import QtQuick 2.15

Item {
    property int cardWidth: 400
    width: cardWidth
    property string frontText: ""
    property string backText: ""
    implicitHeight: row.implicitHeight
    Row {
        id: row
        spacing: 50
        MyTextArea {
            label: "Front card"
            inputWidth: (cardWidth - 50) / 2
            text: frontText
        }

        MyTextArea {
            label: "Back card"
            inputWidth: (cardWidth - 50) / 2
            text: backText
        }
    }
}
