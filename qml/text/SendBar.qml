import QtQuick 2.9
import QtQuick.Controls 2.3

Row {
    signal sended(string text);
    id: basicRow
    spacing: 10
    width: parent.width
    TextField {
        id: sendTextfield
        width: basicRow.width - basicRow.spacing - sendButton.width
        selectByMouse: true
        placeholderText: "URI"
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
                //                    getButton.checked = true
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
                        "GET")
            sended(message)
        }
    }
}
