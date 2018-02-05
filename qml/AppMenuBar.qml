import QtQuick 2.9
import QtQuick.Controls 2.3

MenuBar {
    signal newConnection();
    Menu {
        title: qsTr("连接")
        Action {
            text: qsTr("新连接")
            shortcut: StandardKey.New
            onTriggered: {
                newConnection();
            }
        }
    }
//    Menu {
//        title: qsTr("帮助")
//        Action {
//            text: qsTr("关于")
//        }
//    }
}
