import QtQuick
import QtQuick.Controls

ScrollView {
    width: parent.width
    height: parent.height
    ListView {
        id: crewList
        width: parent.width
        model: crewListModel
        delegate: 
            Rectangle {
                border.color: "black"
                implicitHeight: column.implicitHeight
                implicitWidth: column.implicitWidth
                Column {
                    id: column
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
                        text: "title: " + model.title
                    }
                }
            }
    }
}