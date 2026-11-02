import QtQuick
import QtQuick.Controls

Column {
    Row {
        id: nextImmediateRoomsAndSkills
        width: parent.width
        height: parent.height / 2
        
        Column {
            width: parent.width / 2
            height: parent.height
            Text {
                id: nextImmediateRoomsText
                width: parent.width
                wrapMode: Text.Wrap
                text: qsTr("Next Immediate Rooms")
            }
            ScrollView {
                id: nextImmediateRooms
                width: parent.width
                height: parent.height - nextImmediateRoomsText.implicitHeight
                ListView {
                    id: nextImmediateRoomsList
                    width: parent.width
                    model: nextImmediateRoomsCrewMemberDetailsModel
                    delegate: 
                        Rectangle {
                            border.color: "black"
                            height: nextImmediateRoomsColumn.implicitHeight
                            width: nextImmediateRoomsList.width
                            Column {
                                id: nextImmediateRoomsColumn
                                width: parent.width
                                Text {
                                    width: parent.width
                                    wrapMode: Text.Wrap
                                    text: "id: " + model.id
                                }

                                Text {
                                    width: parent.width
                                    wrapMode: Text.Wrap
                                    text: "name: " + model.name
                                }

                                Text {
                                    width: parent.width
                                    wrapMode: Text.Wrap
                                    text: "type: " + model.type
                                }

                                Button {
                                    text: qsTr("Select")
                                    onClicked: {
                                        roomSelectedEvent.selectRoom(model.id);
                                    }
                                }
                            }
                        }
                }
            }
        }
        Column {
        }
    }
    Column {
    }
}
