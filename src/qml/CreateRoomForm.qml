import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {

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

    Button {
        text: qsTr("Create")
        onClicked: {
            createRoomEvent.createRoom(
                nameInput.text,
                crewCapacityInput.text,
                storageCapacityInput.text,
                sizeInput.text,
                roomTypeComboBox.currentValue,
                [] // TODO: adjacent rooms
            )
        }
    }
}