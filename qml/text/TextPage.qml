import QtQuick 2.9
import QtQuick.Controls 2.3

Page {
    Rectangle {
        anchors.fill: parent
        color: backgroundColor
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
            textModel.append({ "source":"server", "message":text })
        }
        onConnected: {
            textModel.append({ "source":"info", "message":
                                 qsTr("已连接到服务器 ")+client.getAddress()+":"+client.getPort() })
        }
        onSocketError: {
            textModel.append({ "source":"info", "message":error_string })
        }
    }
    Component {
        id: textlistDelegate
        Rectangle {
            id: messageRec
            width: textLabel.width + textList.anchors.margins
            height: textLabel.height + textList.anchors.margins
            radius: 10
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onClicked: {

                }
            }
            TextInput {
                id: textLabel
                anchors.centerIn: parent
                color: "white"
                readOnly: true
                selectByMouse: true
                text: message
            }
            Component.onCompleted: {
                switch(source) {
                case "server":
                    color =  promptColor
                    anchors.left = parent.left
                    break
                case "client":
                    color = emphasizeColor
                    anchors.right = parent.right
                    break
                case "info":
                    color = generalColor
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
        onSended: {
            textModel.append({ "source":"client", "message":text })
        }
    }
}
