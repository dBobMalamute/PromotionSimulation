import QtQuick 2.12
import QtQuick.Shapes 1.12

Item
{
    id: root
    property color groupColor: "black"
    property string groupName: "Name"

    height: 16
    width: 120

    Rectangle
    {
        color: groupColor
        height: parent.height
        width: 16
    }

    Text
    {
        text: groupName
        anchors.verticalCenter: parent.verticalCenter
        x: 18
        font.pointSize: 10
        font.bold: true
        color: "#acacac"
    }
}
