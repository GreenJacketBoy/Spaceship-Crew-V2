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

        Button {
            text: qsTr("Create")
            onClicked: {
                createCrewMemberEvent.createCrewMember(
                    nameInput.text,
                    titleInput.text,
                    []
                )
            }
        }
    }
}
