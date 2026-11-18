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
            Column {
                id: skillsTextAndAddMenu
                height: skillsText.implicitHeight + (crewMemberDetailsAddSkillMap.isEditing ? (addLevelInputRow.height + addSkillComboBoxRow.height + saveNewSkillButton.height + cancelNewSkillButton.height) : addNewSkillButton.height)
                Text {
                    id: skillsText
                    width: parent.width
                    wrapMode: Text.Wrap
                    text: qsTr("Skills")
                }
                StackLayout {
                    width: skillsList.width
                    currentIndex: crewMemberDetailsAddSkillMap.isEditing ? 0 : 1
                    Column {

                        Row {
                            id: addSkillComboBoxRow
                            Text { text: qsTr("Add skill: ") }
                            ComboBox {
                                id: addSkillComboBox
                                model: addSkillModel
                                textRole: "text"
                                valueRole: "value"
                            }
                        }

                        Row {
                            id: addLevelInputRow
                            Text { text: qsTr("Level (number): ") }
                            Rectangle {
                                width: addLevelInput.width; height: addLevelInput.implicitHeight
                                border.color: "black"
                                TextInput {
                                    id: addLevelInput
                                    width: 30
                                    validator: IntValidator { bottom: 0 }
                                }
                            }
                        }

                        Button {
                            id: saveNewSkillButton
                            text: qsTr("Add Skill")
                            onClicked: {
                                crewMemberDetailsAddSkillMap.save(addSkillComboBox.currentValue, addLevelInput.text);
                            }
                        }
                        Button {
                            id: cancelNewSkillButton
                            text: qsTr("Cancel")
                            onClicked: {
                                crewMemberDetailsAddSkillMap.cancel();
                            }
                        }
                    }

                    Column {
                        Button {
                            id: addNewSkillButton
                            text: qsTr("Add new")
                            onClicked: {
                                    crewMemberDetailsAddSkillMap.edit();
                            }
                        }
                    }
                }
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
                        StackLayout {
                            width: skillsList.width
                            height: (model.isEditing ? skillEditRectangle : skillRectangle).height
                            currentIndex: model.isEditing ? 0 : 1
                            Rectangle {
                                id: skillEditRectangle
                                border.color: "black"
                                height: skillsColumnEdit.implicitHeight
                                width: skillsList.width
                                Column {
                                    id: skillsColumnEdit
                                    width: parent.width
                                    Text {
                                        width: parent.width
                                        wrapMode: Text.Wrap
                                        text: "name: " + model.name
                                    }

                                    Row {
                                        Text { text: qsTr("Level: ") }
                                        
                                        Rectangle {
                                            width: levelInput.width; height: levelInput.implicitHeight
                                            border.color: "black"
                                            TextInput {
                                                id: levelInput
                                                validator: IntValidator { bottom: 0 }
                                                text: model.level
                                                width: 30
                                            }
                                        }
                                    }

                                    Button {
                                        text: qsTr("Save")
                                        onClicked: {
                                            skillsCrewMemberDetailsModel.save(model.type, levelInput.text);
                                        }
                                    }
                                    Button {
                                        text: qsTr("Cancel")
                                        onClicked: {
                                            skillsCrewMemberDetailsModel.cancel(model.type);
                                        }
                                    }
                                }
                            }
                            Rectangle {
                                id: skillRectangle
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

                                    Button {
                                        text: qsTr("Edit")
                                        onClicked: {
                                            skillsCrewMemberDetailsModel.edit(model.type);
                                        }
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

            Button {
                text: qsTr("Delete")
                onClicked: {
                    crewMemberDeletedEvent.deleteCrewMember(infoCrewMemberDetailsMap.id);
                }
            }
        }
    }
}
