import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
            width: parent.width / 2
            height: parent.height
            Text {
                id: skillsText
                width: parent.width
                wrapMode: Text.Wrap
                text: qsTr("Skills")
            }
            ScrollView {
                id: skills
                width: parent.width
                height: parent.height - skillsText.implicitHeight
                ListView {
                    id: skillsList
                    width: parent.width
                    model: skillsCrewMemberDetailsModel
                    delegate: 
                        Rectangle {
                            border.color: "black"
                            height: skillsColumn.implicitHeight
                            width: skillsList.width
                            Column {
                                id: skillsColumn
                                width: parent.width
                                Text {
                                    width: parent.width
                                    wrapMode: Text.Wrap
                                    text: "name: " + model.name
                                }

                                Text {
                                    width: parent.width
                                    wrapMode: Text.Wrap
                                    text: "level: " + model.level
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
        currentIndex: editInfoCrewMemberDetailsMap.isEditing ? 0 : 1
        Column {
            id: editCrewMemberInfos
            width: parent.width
            height: parent.height
            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "id: " + editInfoCrewMemberDetailsMap.id
            }

            Row {
                Text { text: qsTr("Name: ") }
                
                Rectangle {
                    width: nameInput.width; height: nameInput.implicitHeight
                    border.color: "black"
                    TextInput {
                        id: nameInput
                        text: editInfoCrewMemberDetailsMap.name
                        width: 30
                    }
                }
            }

            Row {
                Text { text: qsTr("Title: ") }
                
                Rectangle {
                    width: titleInput.width; height: titleInput.implicitHeight
                    border.color: "black"
                    TextInput {
                        id: titleInput
                        text: editInfoCrewMemberDetailsMap.title
                        width: 30
                    }
                }
            }

            Row {
                Text { text: qsTr("Current Room: ") }
                ComboBox {
                    id: currentRoom
                    currentValue: editInfoCrewMemberDetailsMap.currentRoom
                    model: editCurrentRoomModel
                    textRole: "text"
                    valueRole: "value"
                }
            }
            Button {
                text: qsTr("Save")
                onClicked: {
                    editInfoCrewMemberDetailsMap.save(
                        nameInput.text,
                        titleInput.text,
                        currentRoom.currentValue,
                    );
                }
            }
            Button {
                text: qsTr("Cancel")
                onClicked: {
                    editInfoCrewMemberDetailsMap.cancel();
                }
            }
        }
        Column {
            id: crewMemberInfos
            width: parent.width
            height: parent.height
            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "id: " + infoCrewMemberDetailsMap.id
            }

            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "name: " + infoCrewMemberDetailsMap.name
            }

            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "title: " + infoCrewMemberDetailsMap.title
            }

            Text {
                width: parent.width
                wrapMode: Text.Wrap
                text: "current room: " + infoCrewMemberDetailsMap.currentRoom
            }

            Button {
                text: qsTr("Edit")
                onClicked: {
                    editInfoCrewMemberDetailsMap.openEditMenu();
                }
            }
        }
    }
}
