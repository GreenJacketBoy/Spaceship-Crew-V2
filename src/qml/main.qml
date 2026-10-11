import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    visible: true
    width: 400
    height: 400
    title: "Spaceship Crew V2"


    ColumnLayout {
        width: parent.width
        height: parent.height
        TabBar {
            id: bar
            width: parent.width
            TabButton {
                width: bar.parent.width / bar.count
                text: qsTr("Lists")
            }
            TabButton {
                width: bar.parent.width / bar.count
                text: qsTr("Create Room")
            }
            TabButton {
                width: bar.parent.width / bar.count
                text: qsTr("Create Crew Member")
            }
        }

        StackLayout {
            z: bar.z - 1
            height: parent.height - bar.height
            width: parent.width
            currentIndex: bar.currentIndex
            CrewOrRoomTabs { }
            CreateRoomForm { }
            CreateCrewMemberForm { }
        }
    }
}
