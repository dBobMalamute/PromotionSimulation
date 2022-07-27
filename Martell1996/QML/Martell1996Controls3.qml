import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.controlsStyles 1.0

import com.martell1996.extras 1.0

Rectangle
{
    width: 230
    height: 140

    radius: ControlsStyle.radius()
    border.color: ControlsStyle.borderColor()
    border.width: ControlsStyle.borderWidth()

    gradient: Gradient
    {
        GradientStop{ position: 0.05; color: ControlsStyle.gradientTop()}
        GradientStop{position: 0.5; color: ControlsStyle.gradientMid()}
        GradientStop{ position: 0.95; color: ControlsStyle.gradientBottom()}
    }


    Column
    {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10
        Text
        {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Stopping Condition"
            color: ControlsStyle.textColor();
            font: ControlsStyle.textFont();
        }
        Row
        {
            anchors.horizontalCenter: parent.horizontalCenter
            height: cyclesText.height
            width: cyclesText.width + cyclesTextInput.width;
            Text
            {
                id: cyclesText;
                anchors.verticalCenter: parent.verticalCenter
                text: "Cycles: ";
                color: ControlsStyle.textColor();
                font: ControlsStyle.textFont();
            }
            TextInput
            {
                id: cyclesTextInput;
                anchors.verticalCenter: parent.verticalCenter
                validator: IntValidator{bottom: 1; top: 999}
                color: ControlsStyle.textColor();
                font: ControlsStyle.textFont();
                selectByMouse: true;
                onEditingFinished:
                {
                    idea.setCyclesToStopAt(text)
                }

                Component.onCompleted:
                {
                    text = idea.cyclesToStopAt
                }
            }
        }
        Row
        {
            anchors.horizontalCenter: parent.horizontalCenter
            height: checkBox.height
            width: checkBox.width
            CheckBox
            {
                id: checkBox
                anchors.verticalCenter: parent.verticalCenter
                text: "Stop at No Originals"
                font.bold: true
                font.pointSize: 10
                checked: idea.stopAtNoOriginals;
                onCheckedChanged:
                {
                    idea.setStopAtNoOriginals(checked);
                }

                Rectangle
                {
                    anchors.fill: parent
                    anchors.margins: 2
                    z: -1
                    color: "grey"
                }
            }
        }
    }
}
