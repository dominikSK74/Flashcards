import QtQuick
import QtQuick.Controls.Fusion
import "authorization"
import "components"
import "dashboard"

ApplicationWindow {
    id: window
    minimumWidth: 720
    minimumHeight: 480
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

        Connections {
            target: loginController
            function onBackToSignIn() {
                stackView.pop(stackView.depth - 1)
            }
        }

        Connections {
            target: firebaseController
            function onLogout() {
                loginController.logout();
            }
        }

        Connections {
          target: loginController
          function onAuthorizationSuccess() {
            stackView.push("dashboard/dashboard.qml");
            window.visibility = Window.Maximized;
          }
          function onErrorChanged(msg) {
            console.log("Error:", msg)
          }
        }

        Component.onCompleted: {
            if (session.loggedIn) {
                stackView.push("dashboard/dashboard.qml");
                window.visibility = Window.Maximized;
            }
        }

    }
}
