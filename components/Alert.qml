import QtQuick 2.15
import QtQuick.Layouts

Item {
    id: root
    height: 45
    z: 2
    width: container.width

    anchors {
        bottom: parent.bottom
        bottomMargin: 25
        horizontalCenter: parent.horizontalCenter
    }

    // TYPES: info, warning, error, success
    property string type: "info"
    property string message: ""
    property string appFont: "Josefin Sans"
    signal clicked();

    property color backgroundColor: {
        switch(type){
            case "info":
                "#e6f4ff"
                break;
            case "error":
                "#ffe5e9"
                break;
            case "success":
                "#e7ffec"
                break;
            case "warning":
                "#fff5e7"
                break;
        }
    }
    property color textColor: {
        switch(type){
            case "info":
                "#183f75"
                break;
            case "error":
                "#620303"
                break;
            case "success":
                "#007c24"
                break;
            case "warning":
                "#7f4b25"
                break;
        }
    }

    property color borderColor: {
        switch(type){
            case "info":
                "#d0c2b0"
                break;
            case "error":
                "#d0b2b4"
                break;
            case "success":
                "#acd0bd"
                break;
            case "warning":
                "#d0c2b0"
                break;
        }
    }

    property string iconSource: {
        switch(type){
            case "info":
                "qrc:assets/info-icon.svg"
                break;
            case "error":
                "qrc:assets/error-icon.svg"
                break;
            case "success":
                "qrc:assets/success-icon.svg"
                break;
            case "warning":
                "qrc:assets/warning-icon.svg"
                break;
        }
    }

    property string closeIconSource: {
        switch(type){
            case "info":
                "qrc:assets/blue-close-icon.svg"
                break;
            case "error":
                "qrc:assets/r-close-icon.svg"
                break;
            case "success":
                "qrc:assets/g-close-icon.svg"
                break;
            case "warning":
                "qrc:assets/b-close-icon.svg"
                break;
        }
    }

    Rectangle {
        id: container
        height: root.height
        color: root.backgroundColor
        border.color: root.borderColor
        radius: 10

        width: Math.max(120, rowLayout.implicitWidth + 32)

        RowLayout {
            id: rowLayout
            anchors.centerIn: parent
            spacing: 16

            Image {
                source: root.iconSource
                Layout.preferredWidth: 32
                Layout.preferredHeight: 32
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 32
                sourceSize.height: 32
            }

            Text {
                text: root.message
                color: root.textColor
                font.family: root.appFont
                font.pixelSize: 18
                Layout.alignment: Qt.AlignVCenter
            }

            Image {
                source: root.closeIconSource
                Layout.preferredWidth: 32
                Layout.preferredHeight: 32
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 32
                sourceSize.height: 32

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.clicked();
                    }
                }
            }
        }
    }
}
