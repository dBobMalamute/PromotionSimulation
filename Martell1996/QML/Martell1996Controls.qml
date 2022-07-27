import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.controlsStyles 1.0

import com.martell1996.extras 1.0

Rectangle
{
    width: 230
    height: 80

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
        Text
        {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Animation Options"
            color: ControlsStyle.textColor();
            font: ControlsStyle.textFont();
        }
        Row
        {
            id: speedRow
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Button
            {
                enabled: idea.valid
                text: "Step";
                width: 80
                height: 40
                onClicked:
                {
                    idea.animationStepButtonClicked();
                }
            }
            Button
            {
                enabled: idea.valid
                text: "Reset";
                width: 80
                height: 40
                onClicked:
                {
                    idea.animationResetButtonClicked();
                }
            }
        }
    }
}
