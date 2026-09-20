import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    width: 200
    height: parent.height
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
        z: bar.z - 1
        height: parent.height - bar.height
        anchors.bottom: parent.bottom
        width: parent.width
        currentIndex: bar.currentIndex
        RoomList {}
        CrewList {}
    }
}
