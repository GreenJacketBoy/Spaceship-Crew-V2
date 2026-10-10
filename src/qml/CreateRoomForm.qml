import QtQuick
import QtQuick.Controls

ScrollView {
    width: parent.width
    height: parent.height
    Column {
        width: parent.width
        // height: parent.height
        Row {
            Text { text: qsTr("Name: ") }
            
            Rectangle {
                width: nameInput.width; height: nameInput.implicitHeight
                border.color: "black"
                TextInput {
                    id: nameInput
                    width: 30
                }
            }
        }

        Row {
            Text { text: qsTr("Crew capacity: ") }
            Rectangle {
                width: crewCapacityInput.width; height: crewCapacityInput.implicitHeight
                border.color: "black"
                TextInput {
                    id: crewCapacityInput
                    // TODO: right now the highest possible value is "only" the highest value of a signed int, while size_t are used to store
                    validator: IntValidator { bottom: 0 }
                    width: 30
                }
            }
        }

        Row {
            Text { text: qsTr("Storage capacity: ") }
            Rectangle {
                width: storageCapacityInput.width; height: storageCapacityInput.implicitHeight
                border.color: "black"
                TextInput {
                    id: storageCapacityInput
                    width: 30
                    // TODO: right now the highest possible value is "only" the highest value of a signed int, while size_t are used to store
                    validator: IntValidator { bottom: 0 }
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
                    width: 30
                    // TODO: right now the highest possible value is "only" the highest value of a signed int, while size_t are used to store
                    validator: IntValidator { bottom: 0 }
                }
            }
        }

        Row {
            Text { text: qsTr("Room Type: ") }
            ComboBox {
                id: roomTypeComboBox
                model: roomTypeModel
                textRole: "text"
                valueRole: "value"
            }
        }

        Row {
            Text { text: qsTr("Add adjacent room: ") }
            ComboBox {
                id: addAdjacentRoomComboBox
                model: addAdjacentRoomModel
                textRole: "text"
                valueRole: "value"
            }
        }

        Button {
            text: qsTr("Add room")
            onClicked: {
                adjacentRoomListCreateRoom.model.adjacentRoomAddedCreateForm(
                    addAdjacentRoomComboBox.currentValue // maybe value doesn't work because it's a templated function
                )
            }
        }

        ListView {
            id: adjacentRoomListCreateRoom
            width: parent.width
            height: contentHeight
            model: adjacentRoomsListCreateRoomModel
            delegate: 
                Rectangle {
                    border.color: "black"
                    height: column.implicitHeight
                    width: adjacentRoomListCreateRoom.width
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
                            text: qsTr("Remove")
                            onClicked: {
                                adjacentRoomListCreateRoom.model.adjacentRoomRemovedCreateForm(
                                    model.id
                                )
                            }
                        }
                    }
                }
        }

        Button {
            text: qsTr("Create")
            onClicked: {
                createRoomEvent.createRoom(
                    nameInput.text,
                    crewCapacityInput.text,
                    storageCapacityInput.text,
                    sizeInput.text,
                    roomTypeComboBox.currentValue,
                    adjacentRoomListCreateRoom.model.getAdjacentRooms()
                )
            }
        }
    }
}