import QtQuick 2.9
import QtQuick.Controls 2.3
import EO.Message 1.0

Page {
    property bool sendbarEnable: false
    Rectangle {
        anchors.fill: parent
        color: settings.backgroundColor
    }

    ListView {
        id: textList
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: sendBar.top
        anchors.margins: 20
        spacing: 20
        clip: true
        model: textModel
        delegate: textlistDelegate
        currentIndex: count - 1
    }
    ListModel {
        id: textModel
    }
    Connections {
        target: client
        onReceived: {
            textModel.append({ "source":"server", "showText":message_string})
        }
        onConnected: {
            textModel.append({ "source":"info",
                                 "showText": qsTr("已连接到服务器 ")+client.getAddress()+":"+client.getPort()})
        }
        onSocketError: {
            textModel.append({ "source":"info", "showText":error_string})
        }
    }
    Component {
        id: textlistDelegate
        Rectangle {
            id: messageRec
            width: textLabel.width + imageLabel.width + textList.anchors.margins
            height: textLabel.height + imageLabel.height + textList.anchors.margins
            radius: 10
            Image {
                id: imageLabel
//                source: "image://serverImage/foobar"
            }

            TextEdit {
                id: textLabel
                anchors.centerIn: parent
                color: "white"
                readOnly: true
                selectByMouse: true
                text: showText
            }
            Component.onCompleted: {
                switch(source) {
                case "server":
                    color =  settings.promptColor
                    anchors.left = parent.left
                    break
                case "client":
                    color = settings.emphasizeColor
                    anchors.right = parent.right
                    break
                case "info":
                    color = settings.generalColor
                    textLabel.color = "black"
                    anchors.horizontalCenter = parent.horizontalCenter
                    break
                default:

                }
            }
        }
    }

    SendBar {
        id: sendBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        enabled: sendbarEnable
        onSended: {
            textModel.append({ "source":"client", "showText":text })
        }
    }
}
