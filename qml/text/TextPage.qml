import QtQuick 2.9
import QtQuick.Controls 2.3

Page {
    Label {
        id: messageLabel
        anchors.fill: parent
        anchors.margins: 20
        Connections {
            target: client
            onReceived: {
                messageLabel.text += text
            }
        }
    }
    SendBar {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }
}
