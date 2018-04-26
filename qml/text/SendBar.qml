import QtQuick 2.9
import QtQuick.Controls 2.3

Column {
    id: sendbarRoot
    signal sended(string text);
    Row {
        id: basicRow
        spacing: 10
        width: parent.width
        TextField {
            id: sendTextfield
            width: sendbarRoot.width - basicRow.spacing * 2 - sendButton.width - proButton.width
            selectByMouse: true
            placeholderText: "URL"
            onAccepted: {
                sendButton.clicked()
            }
            Button {
                id: clearButton
                anchors.right: parent.right
                width: height * 0.618
                flat: true
                text: "X"
                visible: sendTextfield.text
                onClicked: {
                    sendTextfield.clear()
                    getButton.checked = true
                    headerTextfiled.clear()
                    dataTextfield.clear()
                }
            }
        }
        Button {
            id: sendButton
            text: qsTr("发送")
            enabled: sendTextfield.text

            onClicked: {
                var message =
                        client.sendInputText(
                            sendTextfield.text,
                            (postButton.checked ? "POST":"GET"),
                            headerTextfiled.text,
                            dataTextfield.text)
                sended(message)
            }
        }
        Button {
            id: proButton
            width: 30
            text: qsTr("……")
            onClicked: {
                if (sendbarRoot.state == "") {
                    sendbarRoot.state = "pro"
                }
                else {
                    sendbarRoot.state = ""
                }
            }
        }
    }
    Row {
        id: methodRow
        visible: false
        RadioButton {
            id: getButton
            text: "GET"
            checked: true
        }
        RadioButton {
            id: postButton
            text: "POST"
        }
    }
    TextArea {
        id: headerTextfiled
        visible: false
        selectByMouse: true
        placeholderText: qsTr("请求头部，键值间以\":\"分隔，多个字段间以\"\\n\"分隔")
        width: parent.width
    }
    TextArea {
        id: dataTextfield
        visible: false
        selectByMouse: true
        placeholderText: qsTr("请求数据")
        width: parent.width
    }

    states: [
        State {
            name: "pro"
            PropertyChanges { target: methodRow; visible: true }
            PropertyChanges { target: headerTextfiled; visible: true }
            PropertyChanges { target: dataTextfield; visible: true }
        }
    ]
}
