import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

import "text"
import "camera"

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("客户端")

    property color emphasizeColor: "MediumVioletRed"
    property color backgroundColor: "LightSlateGray"

    Component.onCompleted: {
        connectioDialog.open()
    }

    Settings {
        id: settings
        property string serverAddress: "127.0.0.1"
        property int serverPort: 1240
        property bool serverAutoconnect: false
    }

    menuBar: AppMenuBar {
        onNewConnection: {
            connectioDialog.open()
        }
    }

    SwipeView {
        id: mainSwpieview
        anchors.fill: parent
        TextPage {

        }
        CameraPage {

        }
    }

    header: TabBar {
        currentIndex: mainSwpieview.currentIndex
        Repeater {
            model: [qsTr("文本"), qsTr("摄像头")]
            delegate: TabButton {
                text: modelData
                onClicked: mainSwpieview.currentIndex = index
            }
        }
    }

    ConnectionDialog {
        id: connectioDialog
//        width: parent.width * 0.618
//        height: parent.height * 0.618
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
    }
}
