import QtQuick
import QtQuick.Controls.Fusion
import "authorization"
import "components"

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Flashcards")

    FontLoader {
        id: josefin
        source: "qrc:/fonts/JosefinSans-Regular.ttf"
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "authorization/SignInForm.qml"
    }
}
