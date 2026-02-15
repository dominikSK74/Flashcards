import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    width: inputWidth
    height: labelItem.height + input.height + 8

    property alias text: input.text
    property string label: "Label"
    property string placeholderText: ""
    property bool passwordMode: false
    property string appFont: "Josefin Sans"
    property color backgroundColor: "#212224"
    property color normalColor: "#9f86ff"
    property int inputWidth: 300
    property color fontWhiteColor: "#f9fafc"

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

        TextField {
            id: input
            height: 38
            width: inputWidth
            font.family: appFont
            placeholderText: root.placeholderText
            echoMode: root.passwordMode
                      ? TextInput.Password
                      : TextInput.Normal

            font.pixelSize: 14
            color: fontWhiteColor

            background: Rectangle {
                radius: 6
                color: backgroundColor
                border.color: input.activeFocus ? normalColor : "#2a2a2a"
                border.width: 1
            }
        }
    }
}
