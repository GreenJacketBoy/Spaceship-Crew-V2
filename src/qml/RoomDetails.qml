import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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

                                Button {
                                    text: qsTr("Select")
                                    onClicked: {
                                        crewMemberSelectedEvent.selectCrewMember(model.id);
                                    }
                                }
                            }
                        }
                }
            }
        }
    }
    StackLayout {
        width: parent.width
        height: parent.height / 2
        currentIndex: editInfoRoomDetailsMap.isEditing ? 0 : 1
        Column {
            id: editRoomInfos
            width: parent.width
            height: parent.height / 2
            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "id: " + infoRoomDetailsMap.id
            }

            Row {
                Text { text: qsTr("Name: ") }
                
                Rectangle {
                    width: nameInput.width; height: nameInput.implicitHeight
                    border.color: "black"
                    TextInput {
                        id: nameInput
                        text: editInfoRoomDetailsMap.name
                        width: 30
                    }
                }
            }

            Row {
                Text { text: qsTr("Type: ") }
                ComboBox {
                    id: roomType
                    currentValue: editInfoRoomDetailsMap.type
                    model: editRoomTypeModel
                    textRole: "text"
                    valueRole: "value"
                }
            }

            Row {
                Text { text: qsTr("Crew Capacity: ") }
                
                Rectangle {
                    width: crewCapacityInput.width; height: crewCapacityInput.implicitHeight
                    border.color: "black"
                    TextInput {
                        id: crewCapacityInput
                        validator: IntValidator { bottom: 0 }
                        text: editInfoRoomDetailsMap.crewCapacity
                        width: 30
                    }
                }
            }
            Row {
                Text { text: qsTr("Storage Capacity: ") }
                
                Rectangle {
                    width: storageCapacityInput.width; height: storageCapacityInput.implicitHeight
                    border.color: "black"
                    TextInput {
                        id: storageCapacityInput
                        validator: IntValidator { bottom: 0 }
                        text: editInfoRoomDetailsMap.storageCapacity
                        width: 30
                    }
                }
            }
            Row {
                Text { text: qsTr("Size: ") }
                
                Rectangle {
                    width: sizeInput.width; height: sizeInput.implicitHeight
                    border.color: "black"
                    TextInput {
                        id: sizeInput
                        validator: IntValidator { bottom: 0 }
                        text: editInfoRoomDetailsMap.size
                        width: 30
                    }
                }
            }
            Button {
                text: qsTr("Save")
                onClicked: {
                    editInfoRoomDetailsMap.save(
                        nameInput.text,
                        crewCapacityInput.text,
                        storageCapacityInput.text,
                        sizeInput.text,
                        roomType.currentValue,
                    );
                }
            }
            Button {
                text: qsTr("Cancel")
                onClicked: {
                    editInfoRoomDetailsMap.cancel();
                }
            }
        }
        Column {
            id: roomInfos
            width: parent.width
            height: parent.height / 2
            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "id: " + infoRoomDetailsMap.id
            }

            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "name: " + infoRoomDetailsMap.name
            }

            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "type: " + infoRoomDetailsMap.type
            }
            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "crewCapacity: " + infoRoomDetailsMap.currentCrewAmount + "/" + infoRoomDetailsMap.crewCapacity
            }
            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "storageCapacity: " + infoRoomDetailsMap.storageCapacity
            }
            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "size: " + infoRoomDetailsMap.size
            }
            Button {
                text: qsTr("Edit")
                onClicked: {
                    editInfoRoomDetailsMap.openEditMenu();
                }
            }
        }
    }
}
