import QtQuick 2.9
import QtQuick.Controls 2.3

MenuBar {
    signal newConnection();
    signal closeConnection();
    Menu {
        title: qsTr("连接")
        Action {
            text: qsTr("新连接")
            shortcut: StandardKey.New
            onTriggered: {
                newConnection();
            }
        }
        Action {
            text: qsTr("关闭连接")
            shortcut: StandardKey.Close
            onTriggered: {
                closeConnection();
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
