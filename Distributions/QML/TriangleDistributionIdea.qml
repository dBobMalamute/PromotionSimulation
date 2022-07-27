import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Shapes 1.12

import com.malamute.distributions 1.0

DistributionDisplay
{
    Item
    {
        id: plotArea
        x: 55
        y: 10
        width: 450
        height: 300
        clip: true

        Shape
        {
            id: lowLine
            anchors.fill: parent
            visible: idea.lowVisible && idea.valid

            ShapePath
            {
                id: lowShapePath
                fillColor: "transparent"
                strokeColor: "#40aebf"
                strokeWidth: 2

                strokeStyle: ShapePath.DashLine
                dashPattern: [20, 8];

                startX: 450*(idea.low - idea.xLow) / (idea.xHigh - idea.xLow)
                startY: 0;
                PathLine
                {
                    id: lowPathLine
                    x: 450*(idea.low - idea.xLow) / (idea.xHigh - idea.xLow)
                    y: 300
                }
            }
            Label
            {
                text: "Low"
                y: 10
                x: lowShapePath.startX + 2
                color: "#40aebf"
                font.bold: true
                font.pointSize: 12

                visible: lowShapePath.visible
                ToolTip.text: "Low: " + idea.low.toFixed(3);
                ToolTip.visible: lowMouseArea.containsMouse;
                background: Rectangle
                {
                    anchors.fill: parent
                    radius: 2
                    color: "black"
                    z: -1
                }
                MouseArea
                {
                    id: lowMouseArea
                    anchors.fill: parent
                    hoverEnabled: true;
                }
            }
        }

        Shape
        {
            id: midLine
            anchors.fill: parent
            visible: idea.midVisible && idea.valid

            ShapePath
            {
                id: midShapePath
                fillColor: "transparent"
                strokeColor: "#40aebf"
                strokeWidth: 2

                strokeStyle: ShapePath.DashLine
                dashPattern: [20, 8];

                startX: 450*(idea.mid - idea.xLow) / (idea.xHigh - idea.xLow)
                startY: 0;
                PathLine
                {
                    id: midPathLine
                    x: 450*(idea.mid - idea.xLow) / (idea.xHigh - idea.xLow)
                    y: 300
                }
            }
            Label
            {
                text: "Mid"
                y: 10
                x: midShapePath.startX + 2
                color: "#40aebf"
                font.bold: true
                font.pointSize: 12

                visible: midShapePath.visible
                ToolTip.text: "Mid: " + idea.mid.toFixed(3);
                ToolTip.visible: midMouseArea.containsMouse;
                background: Rectangle
                {
                    anchors.fill: parent
                    radius: 2
                    color: "black"
                    z: -1
                }
                MouseArea
                {
                    id: midMouseArea
                    anchors.fill: parent
                    hoverEnabled: true;
                }
            }
        }

        Shape
        {
            id: upLine
            anchors.fill: parent
            visible: idea.upVisible && idea.valid

            ShapePath
            {
                id: upShapePath
                fillColor: "transparent"
                strokeColor: "#40aebf"
                strokeWidth: 2

                strokeStyle: ShapePath.DashLine
                dashPattern: [20, 8];

                startX: 450*(idea.up - idea.xLow) / (idea.xHigh - idea.xLow)
                startY: 0;
                PathLine
                {
                    id: upPathLine
                    x: 450*(idea.up - idea.xLow) / (idea.xHigh - idea.xLow)
                    y: 300
                }
            }
            Label
            {
                text: "Up"
                y: 10
                x: upShapePath.startX - width - 2
                color: "#40aebf"
                font.bold: true
                font.pointSize: 12

                visible: upShapePath.visible
                ToolTip.text: "Up: " + idea.up.toFixed(3);
                ToolTip.visible: upMouseArea.containsMouse;
                background: Rectangle
                {
                    anchors.fill: parent
                    radius: 2
                    color: "black"
                    z: -1
                }
                MouseArea
                {
                    id: upMouseArea
                    anchors.fill: parent
                    hoverEnabled: true;
                }
            }
        }
    }

    Row
    {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -10
        CheckBox
        {
            text: "Show Low";
            checked: idea.lowVisible;
            onClicked:
            {
                idea.setLowVisible(checked);
            }
        }
        CheckBox
        {
            text: "Show Mid";
            checked: idea.midVisible
            onClicked:
            {
                idea.setMidVisible(checked)
            }
        }
        CheckBox
        {
            text: "Show Up";
            checked: idea.upVisible
            onClicked:
            {
                idea.setUpVisible(checked)
            }
        }
    }
}
