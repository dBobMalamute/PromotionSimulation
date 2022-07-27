import QtQuick 2.12
import QtQuick.Controls 2.12
import QtCharts 2.3
import QtQuick.Shapes 1.12

import com.malamute.distributions 1.0
import QtQuick.Controls.Material 2.12

DistributionDisplay
{
    Item
    {
        id: plotArea
        x: 55
        y: 10
        width: 450
        height: 300

        Shape
        {
            id: lowLine
            anchors.fill: parent
            visible: idea.valid && idea.boundsShowable[0] && idea.showStatistic[0];

            ShapePath
            {
                id: lowShapePath
                fillColor: "transparent"
                strokeColor: "#40aebf"
                strokeWidth: 2

                strokeStyle: ShapePath.DashLine
                dashPattern: [20, 8];

                startX: 450*(idea.params[0] - idea.xLow) / (idea.xHigh - idea.xLow)
                startY: 0;
                PathLine
                {
                    id: lowPathLine
                    x: 450*(idea.params[0] - idea.xLow) / (idea.xHigh - idea.xLow)
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

                ToolTip.text: "Low: " + idea.params[0].toFixed(3);
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
            id: upLine
            anchors.fill: parent
            visible: idea.valid && idea.boundsShowable[1] && idea.showStatistic[1];

            ShapePath
            {
                id: upShapePath
                fillColor: "transparent"
                strokeColor: "#40aebf"
                strokeWidth: 2

                strokeStyle: ShapePath.DashLine
                dashPattern: [20, 8];

                startX: 450*(idea.params[1] - idea.xLow) / (idea.xHigh - idea.xLow)
                startY: 0;
                PathLine
                {
                    id: upPathLine
                    x: 450*(idea.params[1] - idea.xLow) / (idea.xHigh - idea.xLow)
                    y: 300
                }
            }
            Label
            {
                text: "Up"
                y: 10
                x: upShapePath.startX + 2
                color: "#40aebf"
                font.bold: true
                font.pointSize: 12

                ToolTip.text: "Up: " + idea.params[1].toFixed(3);
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

        Shape
        {
            id: stdevLine
            anchors.fill: parent
            visible: idea.valid && idea.showStatistic[3]

            ShapePath
            {
                id: stdevShapePath
                fillColor: "transparent"
                strokeColor: "#2c3aba"
                strokeWidth: 2

                startX: meanShapePath.startX - 450*(idea.params[3])
                        / (idea.xHigh - idea.xLow);
                startY: 120;
                PathLine
                {
                    id: stdevPathLine
                    x: meanShapePath.startX + 450*(idea.params[3])
                       / (idea.xHigh - idea.xLow);
                    y: 120
                }
            }
            Label
            {
                text: "Stdev"
                x: Math.min((stdevPathLine.x + stdevShapePath.startX) / 2 - width - 2,
                            stdevPathLine.x *0.25 + 0.75*stdevShapePath.startX - width/2)
                y: stdevShapePath.startY - height - 2;
                color: "#2c3aba"
                font.bold: true
                font.pointSize: 12

                ToolTip.text: "Standard Deviation: " + idea.params[3].toFixed(3);
                ToolTip.visible: stdevMouseArea2.containsMouse;
                background: Rectangle
                {
                    anchors.fill: parent
                    radius: 2
                    color: "black"
                    z: -1
                }
                MouseArea
                {
                    id: stdevMouseArea2
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
            Label
            {
                text: "Stdev"
                x: Math.max((stdevPathLine.x + stdevShapePath.startX) / 2 + 2,
                            stdevPathLine.x *0.75 + 0.25*stdevShapePath.startX - width/2)
                y: stdevShapePath.startY - height - 2;
                color: "#2c3aba"
                font.bold: true
                font.pointSize: 12

                ToolTip.text: "Standard Deviation: " + idea.params[3].toFixed(3);
                ToolTip.visible: stdevMouseArea1.containsMouse;
                background: Rectangle
                {
                    anchors.fill: parent
                    radius: 2
                    color: "black"
                    z: -1
                }
                MouseArea
                {
                    id: stdevMouseArea1
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
        }

        Shape
        {
            id: meanLine
            anchors.fill: parent
            visible: idea.valid && idea.showStatistic[2]

            ShapePath
            {
                id: meanShapePath
                fillColor: "transparent"
                strokeColor: "#40aebf"
                strokeWidth: 2

                strokeStyle: ShapePath.DashLine
                dashPattern: [20, 8];

                startX: 450*(idea.params[2] - idea.xLow) / (idea.xHigh - idea.xLow)
                startY: 0;
                PathLine
                {
                    id: meanPathLine
                    x: 450*(idea.params[2] - idea.xLow) / (idea.xHigh - idea.xLow)
                    y: 300
                }
            }
            Label
            {
                text: "Mean"
                y: 10
                x: meanShapePath.startX + 2
                color: "#40aebf"
                font.bold: true
                font.pointSize: 12

                ToolTip.text: "Mean: " + idea.params[2].toFixed(3);
                ToolTip.visible: meanMouseArea.containsMouse;
                background: Rectangle
                {
                    anchors.fill: parent
                    radius: 2
                    color: "black"
                    z: -1
                }
                MouseArea
                {
                    id: meanMouseArea
                    anchors.fill: parent
                    hoverEnabled: true;
                }
            }
        }
    }

    Rectangle
    {
        id: controlRowBackground
        anchors.bottom: parent.bottom
        height: 30
        anchors.right: parent.right
        anchors.rightMargin: 96
        anchors.left: parent.left
        radius: 5
        color: "#050512"

        Row
        {
            id: controlsRow
            anchors.fill: parent
            CheckBox
            {
                text: "Show Low";
                visible: idea.boundsShowable[0];
                checked: idea.showStatistic[0];
                anchors.verticalCenter: parent.verticalCenter
                Material.accent: Material.BlueGrey
                Material.foreground: Material.BlueGrey
                onCheckedChanged:
                {
                    idea.setShowStatistic(0, checked)
                }
            }
            CheckBox
            {
                text: "Show Up";
                visible: idea.boundsShowable[1];
                checked: idea.showStatistic[1];
                anchors.verticalCenter: parent.verticalCenter
                Material.accent: Material.BlueGrey
                Material.foreground: Material.BlueGrey
                onCheckedChanged:
                {
                    idea.setShowStatistic(1, checked)
                }
            }
            CheckBox
            {
                text: "Show Mean";
                checked: idea.showStatistic[2];
                anchors.verticalCenter: parent.verticalCenter
                Material.accent: Material.BlueGrey
                Material.foreground: Material.BlueGrey
                onCheckedChanged:
                {
                    idea.setShowStatistic(2, checked)
                }
            }
            CheckBox
            {
                text: "Show Stdev";
                checked: idea.showStatistic[3];
                anchors.verticalCenter: parent.verticalCenter
                Material.accent: Material.BlueGrey
                Material.foreground: Material.BlueGrey
                onCheckedChanged:
                {
                    idea.setShowStatistic(3, checked)
                }
            }
        }
    }

    //Kurtosis Helper;
    Rectangle
    {
        visible: idea.valid && idea.kurtosisHelper
        width: 66
        height: 16
        radius: 5
        x: -80
        y: 240
        color: "#050512"

        Text
        {
            anchors.centerIn: parent
            color: "teal"
            font.pointSize: 10
            text: ":" + idea.params[5].toPrecision(3)
        }
    }

}
