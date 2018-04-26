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

    Component.onCompleted: {
        connectioDialog.open()
    }

    Settings {
        id: settings
        property color emphasizeColor: "MediumVioletRed"
        property color promptColor: "LightSlateGray"
        property color generalColor: "White"
        property color backgroundColor: "WhiteSmoke"
        property string serverAddress: "127.0.0.1"
        property int serverPort: 1680
        property bool serverAutoconnect: false
    }

    menuBar: AppMenuBar {
        onNewConnection: {
            connectioDialog.open()
        }
        onCloseConnection: {
            client.closeConnection()
            cameraPage.stop()
            cameraClient.closeConnection()
            connectioDialog.connected = false
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

    SwipeView {
        id: mainSwpieview
        anchors.fill: parent
        TextPage {
            sendbarEnable: connectioDialog.connected
        }
        CameraPage {
            id: cameraPage
        }
        onCurrentIndexChanged: {
            connectCurrentClient(connectioDialog.ip, connectioDialog.port)
        }
        function connectCurrentClient(ip, port) {
            client.closeConnection()
            cameraClient.closeConnection()
            cameraPage.stop()

            switch(currentIndex) {
            case 0:
                client.connectToServer(ip, port)
                break
            case 1:
                cameraClient.connectToServer(ip, port)
                cameraPage.start()
                break
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
