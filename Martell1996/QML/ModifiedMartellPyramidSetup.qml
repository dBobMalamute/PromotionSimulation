import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.controlsStyles 1.0

import com.martell1996.extras 1.0

Rectangle
{
    width: 920
    height: 420

    radius: ControlsStyle.radius()
    border.color: ControlsStyle.borderColor()
    border.width: ControlsStyle.borderWidth()

    color: "black"

    Rectangle
    {
        x: 225
        y: 6
        width: 110
        height: 40
        radius: 4
        color: "darkGray"
        Text
        {
            text: "Levels:"
            color: "black"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 10
            font.bold: true
            font.pointSize: 12
        }
        TextInput
        {
            text: idea.numLevels
            color: "black"
            selectByMouse: true
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 10
            font.bold: true
            font.pointSize: 12
            font.underline: true
            validator: IntValidator{bottom: 1; top: 30}
            onEditingFinished:
            {
                idea.setNumLevels(text);
            }
        }
    }

    Column
    {
        width: 540
        height: 360
        x: 10
        y: 50
        spacing: 2

        Repeater
        {
            id: levelsRepeater
            anchors.fill: parent
            model: idea.numLevels
            delegate: Rectangle
            {
                id: rectDelegate
                anchors.horizontalCenter: parent.horizontalCenter
                width: 180 + 360.0 * index / idea.numLevels
                height: (360 / idea.numLevels) - 2
                color: "#3e3124"

                Rectangle
                {
                    width: 10
                    height: 10
                    anchors.verticalCenter: parent.verticalCenter
                    x: 10
                    color: "black"
                }
                Text
                {
                    anchors.verticalCenter: parent.verticalCenter
                    x: 22
                    text: "x" + idea.positionsAtLevel[index]
                }
            }
        }
    }

    Rectangle
    {
        radius: 4
        color: "darkGray"
        y: 6
        width: 80
        height: 40
        x: 560
        Text
        {
            anchors.centerIn: parent
            text: "Positions"
            font.bold: true
            font.pointSize: 12
            color: "black"
        }
    }

    Column
    {
        width: 80
        height: 360
        x: 560
        y: 50
        spacing: 2
        Repeater
        {
            id: numAtLevelRepeater
            anchors.fill: parent
            model: idea.numLevels
            delegate: Rectangle
            {
                width: 80
                height: (360 / idea.numLevels) - 2
                color: "lightgray"
                TextInput
                {
                    anchors.centerIn: parent
                    text: idea.positionsAtLevel[index];
                    font.pointSize: Math.min(10, parent.height - 2)
                    color: "black"
                    font.underline: true;
                    selectByMouse: true
                    validator: IntValidator{top: 100000; bottom: 1}
                    onEditingFinished:
                    {
                        idea.setPositionAtOneLevel(index, text);
                    }
                }
            }
        }
    }

    Rectangle
    {
        radius: 4
        color: "darkGray"
        y: 6
        width: 80
        height: 40
        x: 650
        Text
        {
            anchors.centerIn: parent
            text: "Positive\nAttrition"
            font.bold: true
            font.pointSize: 12
            color: "black"
        }
    }


    Rectangle
    {
        radius: 4
        color: "darkGray"
        y: 6
        width: 80
        height: 40
        x: 740
        Text
        {
            anchors.centerIn: parent
            text: "Random\nAttrition"
            font.bold: true
            font.pointSize: 12
            color: "black"
        }
    }

    Rectangle
    {
        radius: 4
        color: "darkGray"
        y: 6
        width: 80
        height: 40
        x: 830
        Text
        {
            anchors.centerIn: parent
            text: "Negative\nAttrition"
            font.bold: true
            font.pointSize: 12
            color: "black"
        }
    }

    Column
    {
        width: 80
        height: 360
        x: 650
        y: 50
        spacing: 2
        Repeater
        {
            id: attritionAtLevelRepeater
            anchors.fill: parent
            model: idea.numLevels
            delegate: Rectangle
            {
                width: 80
                height: (360 / idea.numLevels) - 2
                color: "lightgray"
                TextInput
                {
                    anchors.centerIn: parent
                    text: idea.positiveAttrition[index];
                    font.pointSize: Math.min(10, parent.height - 2)
                    font.underline: true;
                    selectByMouse: true
                    color: "black"
                    validator: DoubleValidator{top: 1.0; bottom: 0.0}
                    onEditingFinished:
                    {
                        idea.setPositiveAttrition(index, text);
                    }
                }
            }
        }
    }

    Column
    {
        width: 80
        height: 360
        x: 740
        y: 50
        spacing: 2
        Repeater
        {
            anchors.fill: parent
            model: idea.numLevels
            delegate: Rectangle
            {
                width: 80
                height: (360 / idea.numLevels) - 2
                color: "lightgray"
                TextInput
                {
                    anchors.centerIn: parent
                    text: idea.randomAttrition[index];
                    font.pointSize: Math.min(10, parent.height - 2)
                    font.underline: true;
                    selectByMouse: true
                    color: "black"
                    validator: DoubleValidator{top: 1.0; bottom: 0.0}
                    onEditingFinished:
                    {
                        idea.setRandomAttrition(index, text);
                    }
                }
            }
        }
    }

    Column
    {
        width: 80
        height: 360
        x: 830
        y: 50
        spacing: 2
        Repeater
        {
            anchors.fill: parent
            model: idea.numLevels
            delegate: Rectangle
            {
                width: 80
                height: (360 / idea.numLevels) - 2
                color: "lightgray"
                TextInput
                {
                    anchors.centerIn: parent
                    text: idea.negativeAttrition[index];
                    font.pointSize: Math.min(10, parent.height - 2)
                    font.underline: true;
                    selectByMouse: true
                    color: "black"
                    validator: DoubleValidator{top: 1.0; bottom: 0.0}
                    onEditingFinished:
                    {
                        idea.setNegativeAttrition(index, text);
                    }
                }
            }
        }
    }
}
