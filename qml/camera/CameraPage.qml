import QtQuick 2.9
import QtQuick.Controls 2.3

Page {
    Image {
        id: image
        anchors.fill: parent
        cache: false
    }

    Timer {
        id: refreshTimer
        interval: 50
        repeat: true
        onTriggered: {
            cameraClient.sendInputText("/image")
        }
    }
    function start() {
        refreshTimer.start()
    }
    function stop() {
        refreshTimer.stop()
    }
    Connections{
        target: cameraClient
        onReceivedImage: {
            image.source = ""
            image.source = "image://cameraResource/0"
        }
    }
}
