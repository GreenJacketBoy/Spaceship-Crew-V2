import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    visible: true
    width: 400
    height: 400
    title: "Spaceship Crew V2"

    Button {
        text: "SPACESHIP !"
        anchors.centerIn: parent
    }
    CrewOrRoomTabs {
        height: parent.height
    }
}
