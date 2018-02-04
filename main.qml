import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("客户端")

    property color emphasizeColor: "MediumVioletRed"
    property color backgroundColor: "LightSlateGray"

    Settings {
        id: settings
        property string serverAddress: "127.0.0.1"
        property int serverPort: 1240
    }
    Component.onCompleted: {
        connectioDialog.open()
    }

    ConnectionDialog {
        id: connectioDialog
//        width: parent.width * 0.618
//        height: parent.height * 0.618
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
    }
}
