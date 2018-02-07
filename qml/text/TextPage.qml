import QtQuick 2.9
import QtQuick.Controls 2.3

Page {
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
        currentIndex: count
    }
    ListModel {
        id: textModel
    }
    Connections {
        target: client
        onReceived: {
            textModel.append({ "source":"server", "message":text })
        }
    }
    Component {
        id: textlistDelegate
        Rectangle {
            width: textLabel.width + textList.anchors.margins
            height: textLabel.height + textList.anchors.margins
            color: source=="client" ? emphasizeColor : promptColor
            radius: 10
            Label {
                id: textLabel
                anchors.centerIn: parent
                color: "white"
                text: message
            }
            Component.onCompleted: {
                if (source == "client") {
                    anchors.right = parent.right
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
