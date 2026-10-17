import QtQuick
import QtQuick.Controls

Column {
    Row {
        id: adjacentRoomsAndCreMembersInRoom
        width: parent.width
        height: parent.height / 2
        
        Column {
            width: parent.width
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
                            height: column.implicitHeight
                            width: adjacentRoomList.width
                            Column {
                                id: column
                                width: parent.width
                                Text {
                                    id: textId
                                    width: parent.width
                                    wrapMode: Text.Wrap
                                    text: "id: " + model.id
                                }

                                Text {
                                    id: textName
                                    width: parent.width
                                    wrapMode: Text.Wrap
                                    text: "name: " + model.name
                                }

                                Text {
                                    id: textType
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
        Column { }
    }
    Row {
        id: roomInfos
        width: parent.width
        height: parent.height / 2
    }
}
