import QtQuick 2.9
import QtQuick.Controls 2.3

Row {
    spacing: 20
    TextField {
        id: sendTextfield
        width: parent.width - parent.spacing - sendButton.width
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
                sendTextfield.text = ""
            }
        }
    }
    Button {
        id: sendButton
        text: qsTr("发送")
        enabled: sendTextfield.text
        onClicked: {
            client.sendText(sendTextfield.text)
        }
    }
}