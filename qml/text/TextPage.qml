import QtQuick 2.9
import QtQuick.Controls 2.3

Page {
    id: textPageRoot
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
            textModel.append({ "messageType":"Response", "showText":message_string, "resourceIndex":-1})
        }
        onReceivedImage: {
            textModel.append( {"messageType":"Response", "showText": "", "resourceIndex":id})
        }

        onConnected: {
            textModel.append({ "messageType":"Notice",
                                 "showText": qsTr("已连接到服务器 ")+client.getAddress()+":"+client.getPort(),
                                 "resourceIndex":-1})
        }
        onClosedConnection: {
            textModel.append({ "messageType":"Notice", "showText": qsTr("已关闭连接"), "resourceIndex":-1})
        }

        onSocketError: {
            textModel.append({ "messageType":"Notice", "showText":error_string, "resourceIndex":-1})
        }
    }
    Component {
        id: textlistDelegate
        Rectangle {
            id: messageRec
            width: textLabel.width + (imageLabel.visible?imageLabel.width:0) + textList.anchors.margins
            height: textLabel.height + (imageLabel.visible?imageLabel.height:0) + textList.anchors.margins
            radius: 10

            Image {
                id: imageLabel
                property double ratio: 1
                visible: false
                width: textPageRoot.width / 2
                height: width / ratio
                anchors.centerIn: parent
                Component.onCompleted: {
                    if (resourceIndex != -1) {
                        source = "image://resource/"+resourceIndex
                        ratio = width / height
                        visible = true

                    }

                }
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
                switch(messageType) {
                case "Response":
                    color =  settings.promptColor
                    anchors.left = parent.left
                    break
                case "Request":
                    color = settings.emphasizeColor
                    anchors.right = parent.right
                    break
                case "Notice":
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
            textModel.append({ "messageType":"Request", "showText":text, "resourceIndex":-1})
        }
    }
}
