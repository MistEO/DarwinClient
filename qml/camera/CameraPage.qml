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
        interval: settings.cameraRefreshIntv
        repeat: true
        onTriggered: {
            cameraClient.sendInputText("/image")
        }
    }
    MouseArea {
        anchors.fill: image
        acceptedButtons: Qt.RightButton
        onClicked: {
            contentMenu.popup();
        }
    }
    Menu {
        id: contentMenu
        MenuItem {
            text: qsTr("暂停")
            onTriggered: {
                if (refreshTimer.running) {
                    refreshTimer.stop();
                    text = qsTr("开始")
                }
                else {
                    refreshTimer.start();
                    text = qsTr("暂停")
                }
            }
        }
        MenuItem {
            text: qsTr("保存")
            enabled: !refreshTimer.running
            onTriggered: {
                cameraResource.saveImage(0);
            }
        }
        Menu {
            title: qsTr("刷新速率")
//            MenuItem {
//                text: qsTr("60Hz")
//                onTriggered: {
//                    settings.cameraRefreshIntv = 1000 / 60
//                }
//            }
            MenuItem {
                text: qsTr("24Hz")
                onTriggered: {
                    settings.cameraRefreshIntv = 1000 / 24
                }
            }
            MenuItem {
                text: qsTr("10Hz")
                onTriggered: {
                    settings.cameraRefreshIntv = 1000 / 10
                }
            }
            MenuItem {
                text: qsTr("5Hz")
                onTriggered: {
                    settings.cameraRefreshIntv = 1000 / 5
                }
            }
            MenuItem {
                text: qsTr("2Hz")
                onTriggered: {
                    settings.cameraRefreshIntv = 1000 / 2
                }
            }
            MenuItem {
                text: qsTr("1Hz")
                onTriggered: {
                    settings.cameraRefreshIntv = 1000 / 1
                }
            }
            MenuItem {
                text: qsTr("0.5Hz")
                onTriggered: {
                    settings.cameraRefreshIntv = 1000 / 0.5
                }
            }
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
