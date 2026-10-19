import QtQuick
import QtQuick.Controls

ScrollView {
    width: parent.width
    height: parent.height
    Column {
        width: parent.width
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
            Text { text: qsTr("Title: ") }
            
            Rectangle {
                width: nameInput.width; height: nameInput.implicitHeight
                border.color: "black"
                TextInput {
                    id: titleInput
                    width: 30
                }
            }
        }

        Row {
            Text { text: qsTr("Current Room: ") }
            ComboBox {
                id: currentRoom
                model: currentRoomModel
                textRole: "text"
                valueRole: "value"
            }
        }

        Row {
            Text { text: qsTr("Add skill: ") }
            ComboBox {
                id: addSkillComboBox
                model: addSkillModel
                textRole: "text"
                valueRole: "value"
            }
        }

        Row {
            Text { text: qsTr("Level (number): ") }
            Rectangle {
                width: levelInput.width; height: levelInput.implicitHeight
                border.color: "black"
                TextInput {
                    id: levelInput
                    width: 30
                    // TODO: right now the highest possible value is "only" the highest value of a signed int, while size_t are used to store
                    validator: IntValidator { bottom: 0 }
                }
            }
        }

        Button {
            text: qsTr("Add Skill")
            onClicked: {
                skillsList.model.skillAddedCreateForm(
                    addSkillComboBox.currentValue,
                    levelInput.text,
                )
            }
        }

        ListView {
            id: skillsList
            width: parent.width
            height: contentHeight
            model: skillsListCreateCrewMemberModel
            delegate: 
                Rectangle {
                    border.color: "black"
                    height: column.implicitHeight
                    width: skillsList.width
                    Column {
                        id: column
                        width: parent.width
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
                            text: "level: " + model.level
                        }

                        Button {
                            text: qsTr("Remove")
                            onClicked: {
                                skillsList.model.skillRemovedCreateForm(
                                    model.type
                                )
                            }
                        }
                    }
                }
        }

        Button {
            text: qsTr("Create")
            onClicked: {
                createCrewMemberEvent.createCrewMember(
                    nameInput.text,
                    titleInput.text,
                    currentRoom.currentValue,
                    skillsList.model.getSkills()
                )
            }
        }
    }
}
