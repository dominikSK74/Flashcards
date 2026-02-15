import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    width: inputWidth

    property alias text: input.text
    property string label: "Label"
    property string placeholderText: ""
    property string appFont: "Josefin Sans"
    property color backgroundColor: "#212224"
    property color normalColor: "#9f86ff"
    property int inputWidth: 300
    property color fontWhiteColor: "#f9fafc"

    property int minInputHeight: 38
    property int maxInputHeight: 150

    height: labelItem.height + input.height + 8

    Column {
        spacing: 6
        anchors.fill: parent

        Text {
            id: labelItem
            text: root.label
            color: "#9a9a9a"
            font.pixelSize: 12
            font.family: appFont
        }

        TextArea {
            id: input
            width: inputWidth

            placeholderText: root.placeholderText
            font.family: appFont
            font.pixelSize: 14
            color: fontWhiteColor

            wrapMode: Text.Wrap
            selectByMouse: true

            padding: 10

            height: Math.min(
                        maxInputHeight,
                        Math.max(minInputHeight, contentHeight + padding * 2)
                    )

            background: Rectangle {
                radius: 6
                color: backgroundColor
                border.color: input.activeFocus ? normalColor : "#2a2a2a"
                border.width: 1
            }
        }
    }
}
