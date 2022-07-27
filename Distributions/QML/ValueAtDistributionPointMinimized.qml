import QtQuick 2.12

FocusScope
{
    width: Math.max(point.width, value.width)
    height: point.height + value.height + 4

    TextInput
    {
        id: point
        visible: idea.valid;
        font.bold: true
        font.pointSize: 12
        verticalAlignment: TextInput.AlignVCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: "#1a1a1a"
        selectByMouse: true
        readOnly: true
        focus: true;

        text: "point: " + idea.point.toPrecision(3);


        onActiveFocusChanged:
        {
            if(activeFocus)
                point.selectAll();
            else
                point.deselect();
        }
    }
    TextInput
    {
        id: value
        anchors.bottom: parent.bottom
        visible: idea.valid;
        font.bold: true
        font.pointSize: 12
        verticalAlignment: TextInput.AlignVCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: "#1a1a1a"
        selectByMouse: true
        readOnly: true

        text: "value: " + idea.value.toPrecision(3);
    }

    Rectangle
    {
        anchors.fill: parent
        anchors.margins: -3
        border.color: "#1a1a1a"
        border.width: 2
        radius: 2
        color: "#e6e6e6"
        z: -1
    }
}

