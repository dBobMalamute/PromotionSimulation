import QtQuick 2.12


Rectangle
{
    height: 30
    width: 80
    color: "#5a0000"
    radius: 6

    Text
    {
        anchors.centerIn: parent
        font.pointSize: 12
        color: "#cccccc"

        text: idea.areaShown.toPrecision(4);
    }
}
