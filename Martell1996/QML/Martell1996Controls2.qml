import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.controlsStyles 1.0
import com.martell1996.extras 1.0

Rectangle
{
    width: 140
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
        anchors.topMargin: 20
        anchors.fill: parent
        spacing: 10

        Text
        {
            id: bulkRunsText;
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Bulk Runs"
            color: ControlsStyle.textColor();
            font: ControlsStyle.textFont();
        }
        Row
        {
            anchors.horizontalCenter: parent.horizontalCenter
            height: runsText.height
            width: runsText.width + runsTextInput.width;
            Text
            {
                id: runsText;
                anchors.verticalCenter: parent.verticalCenter
                text: "Runs: ";
                color: ControlsStyle.textColor();
                font: ControlsStyle.textFont();
            }
            TextInput
            {
                id: runsTextInput;
                anchors.verticalCenter: parent.verticalCenter
                validator: IntValidator{bottom: 1; top: 999}
                color: ControlsStyle.textColor();
                font: ControlsStyle.textFont();
                selectByMouse: true;
                onEditingFinished:
                {
                    idea.setBulkRunNum(text)
                }

                Component.onCompleted:
                {
                    text = idea.bulkRunNum
                }
            }
        }

        Button
        {
            enabled: idea.valid
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Start";
            onClicked:
            {
                idea.bulkRun();
            }
        }
    }
}

