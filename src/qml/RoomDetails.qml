import QtQuick
import QtQuick.Controls

Column {
    Row {
        id: adjacentRoomsAndCreMembersInRoom
        width: parent.width
        height: parent.height / 2
        
        Column {
            width: parent.width / 2
            height: parent.height
            Text {
                id: adjacentRoomsText
                width: parent.width
                wrapMode: Text.Wrap
                text: qsTr("Adjacent Rooms")
            }
            ScrollView {
                id: adjacentRooms
                width: parent.width
                height: parent.height - adjacentRoomsText.implicitHeight
                ListView {
                    id: adjacentRoomList
                    width: parent.width
                    model: adjacentRoomListRoomDetailsModel
                    delegate: 
                        Rectangle {
                            border.color: "black"
                            height: roomListColumn.implicitHeight
                            width: adjacentRoomList.width
                            Column {
                                id: roomListColumn
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
            width: parent.width / 2
            height: parent.height
            Text {
                id: crewMembersInRoomText
                width: parent.width
                wrapMode: Text.Wrap
                text: qsTr("Crew Members in the Room")
            }
            ScrollView {
                id: crewMembersInRoom
                width: parent.width
                height: parent.height - crewMembersInRoomText.implicitHeight
                ListView {
                    id: crewMembersInRoomList
                    width: parent.width
                    model: crewMemberInRoomDetailsModel
                    delegate: 
                        Rectangle {
                            border.color: "black"
                            height: crewListColumn.implicitHeight
                            width: crewMembersInRoomList.width
                            Column {
                                id: crewListColumn
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
                                    text: "title: " + model.title
                                }
                            }
                        }
                }
            }
        }
    }
    Row {
        id: roomInfos
        width: parent.width
        height: parent.height / 2
    }
}
