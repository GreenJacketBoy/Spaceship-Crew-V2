import QtQuick
import QtQuick.Controls

ScrollView {
    height: parent.height
    width: 200
    ListView {
        width: parent.width; height: parent.height
        model: roomListModel
        delegate: 
            Rectangle {
                border.color: "black"
                implicitHeight: column.implicitHeight
                implicitWidth: column.implicitWidth
                Column {
                    id: column
                    Text {
                        id: textId
                        text: "id: " + model.id
                    }

                    Text {
                        id: textName
                        text: "name: " + model.name
                    }

                    Text {
                        id: textType
                        text: "type: " + model.type
                    }
                }
            }
    }
}