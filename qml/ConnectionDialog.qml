import QtQuick 2.9
import QtQuick.Controls 2.3

Dialog {
    id: connectionDialogRoot
    signal connected();
    title: qsTr("连接到服务器")
    modal: true
    focus: true
    contentItem: Grid {
        id: textfieldGrid
        spacing: 20
        rows: 2
        Column {
            id: addressColumn
            spacing: 5
            Label {
                color: backgroundColor
                opacity: addressTextfield.text.length > 0
                text: addressTextfield.placeholderText
            }
            TextField {
                id: addressTextfield
                focus: true
                placeholderText: qsTr("IP地址")
                text: settings.serverAddress
                onAccepted: {
                    portTextfield.focus = true
                }
            }
        }
        Column {
            id: portColumn
            spacing: 5
            Label {
                color: backgroundColor
                opacity: portTextfield.text.length > 0
                text: portTextfield.placeholderText
            }
            TextField {
                id: portTextfield
                placeholderText: qsTr("端口号")
                text: settings.serverPort
                onAccepted: {
                    connectButton.clicked()
                }
            }
        }
        Row {
            width: addressColumn.width
            height: connectBusyindicator.height
            spacing: 5
            BusyIndicator {
                id: connectBusyindicator
                width: connectButton.height
                visible: false
            }
            Label {
                id: statusLabel
                color: emphasizeColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Item {
            width: portColumn.width
            height: portColumn.height
//            CheckBox {
//                id: autoConnectCheckbox
//                text: qsTr("自动连接")
//                anchors.verticalCenter: parent.verticalCenter
//                checked: settings.serverAutoconnect
//                Component.onCompleted: {
//                    if (checked) {
//                        accepted()
//                    }
//                }
//            }

            Button {
                id: connectButton
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("确定")
                enabled: addressTextfield.text && portTextfield.text
                onClicked: {
                    accepted()
                }
            }
        }
    }

    //    standardButtons: Dialog.Ok

    onAccepted: {
        connectButton.enabled = false
        connectBusyindicator.visible = true
        statusLabel.text = qsTr("正在连接")
        client.connectToServer(addressTextfield.text, portTextfield.text)
        settings.serverAddress = addressTextfield.text
        settings.serverPort = portTextfield.text
//        settings.serverAutoconnect = autoConnectCheckbox.checked
    }
    Connections {
        target: client
        onConnected: {
            connectBusyindicator.visible = false
            connectButton.enabled = true
            statusLabel.text = ""
            connected();
            connectionDialogRoot.close()
        }
        onSocketError: {
            connectBusyindicator.visible = false
            connectButton.enabled = true
            statusLabel.text = error_string
        }
    }
}
