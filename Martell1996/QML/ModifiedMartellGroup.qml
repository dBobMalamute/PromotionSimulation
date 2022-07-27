import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    id: mainRect
    width: Math.max(140, nameRow.width + 4)
    height: 140
    radius: 4

    Component.onCompleted:
    {
        color = idea.getColor()
    }

    Connections
    {
        target: idea
        function onGroupColorChanged(index)
        {
            mainRect.color = idea.getColor()
        }
    }

    Column
    {
        anchors.fill: parent
        anchors.margins: 2
        Row
        {
            id: nameRow;
            spacing: 4
            Text
            {
                text: "Name:"
                font.bold: true
                font.pointSize: 12
            }
            TextInput
            {
                text: idea.groupName
                font.pointSize: 12
                selectByMouse: true
                font.underline: true
                onEditingFinished:
                {
                    idea.setGroupName(text)
                }
            }
        }

        ComboBox
        {
            editable: false
            width: parent.width
            model: ListModel
            {
                ListElement{text: "Women"}
                ListElement{text: "Men"}
                ListElement{text: "Unspecified"}
            }
            onActivated:
            {
                idea.setGroupGenderInt(index);
            }
            Component.onCompleted:
            {
                currentIndex = idea.getGroupGenderInt();
            }
        }
        ComboBox
        {
            id: colorComboBox
            width: parent.width
            editable: false
            currentIndex: idea.groupColor;
            model: ListModel
            {
                id: model
                ListElement {text: "Taupe"}
                ListElement {text: "Emerald"}
                ListElement {text: "Vanilla"}
                ListElement {text: "Tuscany"}
                ListElement {text: "Azure"}
                ListElement {text: "Green"}
                ListElement {text: "Orangish"}
            }
            onCurrentIndexChanged:
            {
                idea.setGroupColor(currentIndex)
            }
        }

        Row
        {
            width: parent.width
            spacing: 4
            Text
            {
                font.bold: true
                font.pointSize: 12
                text: "Percent:"
            }
            TextInput
            {
                text: idea.groupPercent
                font.pointSize: 12
                selectByMouse: true
                validator: DoubleValidator{top: 100.0; bottom: 0.0}
                font.underline: true
                onEditingFinished:
                {
                    idea.setGroupPercent(text);
                }
            }
        }
    }
}
