import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    id: mainRect
    width: text.width + 4
    height: text.height + 4
    radius: 4

    Component.onCompleted:
    {
        color = idea.getColor()
    }

    Text
    {
        anchors.centerIn: parent
        id: text
        text: idea.groupName
        font.pointSize: 12
    }
}
