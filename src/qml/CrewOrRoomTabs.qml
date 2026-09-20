import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    width: 200
    TabBar {
        id: bar
        width: parent.width
        TabButton {
            width: bar.parent.width / bar.children.length
            text: qsTr("Room")
        }
        TabButton {
            width: bar.parent.width / bar.children.length
            text: qsTr("Crew")
        }
    }

    StackLayout {
        Layout.fillWidth: true
        width: parent.width
        currentIndex: bar.currentIndex
        RoomList {
            Layout.fillWidth: true
        }
        CrewList {
            Layout.fillWidth: true
        }
    }
}
