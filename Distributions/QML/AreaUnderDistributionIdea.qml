import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Shapes 1.12

import com.malamute.distributions 1.0

Item
{
    width: 530
    height: 410
    DistributionDisplay
    {
        id: display
        Item
        {
            property bool showAreaEdgeCase : true;

            id: continuousAreaItem
            x: 55
            y: 10
            width: 450
            height: 300
            clip: true
            visible: idea.valid && showAreaEdgeCase;

            Shape
            {
                id: continuousAreaShape
                anchors.fill: parent

                ShapePath
                {
                    id: areaPath
                    fillColor:  "#45ff0000"
                    strokeColor: "transparent"

                    startX: 0;
                    startY: 300;
                }
            }
        }

        function clearArea()
        {
            // Empty the shape path.
            areaPath.pathElements = [];
        }

        Connections
        {
            target: idea;

            function onDisplayArea(xValues, yValues)
            {
                display.clearArea();
                if(xValues.length === 0)
                {
                    continuousAreaItem.showAreaEdgeCase = false;
                    return;
                }
                else
                    continuousAreaItem.showAreaEdgeCase = true;

                //Start the shape path in the correct location.
                areaPath.startX = xValues[0];
                areaPath.startY = 301;

                var pathLine;
                for(var i = 0; i < xValues.length; i++)
                {
                    pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{x: " +
                                                  xValues[i] + "; y: " + yValues[i] + "}",
                                                  areaPath);
                    areaPath.pathElements.push(pathLine);
                }

                pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{x: " +
                                              xValues[xValues.length - 1] + "; y: 301}",
                                              areaPath);
                areaPath.pathElements.push(pathLine);

                pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{x: " +
                                              xValues[0] + "; y: 301}",
                                              areaPath);
                areaPath.pathElements.push(pathLine);
            }
        }
    }
    Rectangle
    {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: 140
        height: 70
        radius: 8
        color: "#342b3b"

        Image
        {
            anchors.top: parent.top
            anchors.left: parent.left
            source: "qrc:/Images/DistributionAreaLowerBound.png"
        }

        Rectangle
        {
            anchors.top: parent.top
            anchors.right: parent.right
            color: "Black"
            width: 70
            height: 40
            TextInput
            {
                anchors.centerIn: parent
                text: idea.lowLimit;
                font.pointSize: 10
                color: idea.lowLimitEnabled ? "#f33c3c" : "#737373";
                selectByMouse: true
                validator: DoubleValidator{}
                onEditingFinished:
                {
                    idea.setLowLimit(text);
                }
            }
        }

        CheckBox
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -8
            text: "Enabled"
            checked: idea.lowLimitEnabled;
            onCheckedChanged:
            {
                idea.setLowLimitEnabled(checked);
            }
        }
    }

    Rectangle
    {
        height: 60
        width: 120
        x: 160
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        color: "#5a0000"
        border.width: 6
        radius: 6
        border.color: "black"

        Text
        {
            anchors.centerIn: parent
            font.pointSize: 12
            color: "#cccccc"

            text: "Area: " + idea.areaShown.toPrecision(4);
        }
    }

    Rectangle
    {
        anchors.bottom: parent.bottom
        x: 300
        width: 140
        height: 70
        radius: 8
        color: "#342b3b"

        Image
        {
            anchors.top: parent.top
            anchors.left: parent.left
            source: "qrc:/Images/DistributionAreaUpperBound.png"
        }

        Rectangle
        {
            anchors.top: parent.top
            anchors.right: parent.right
            color: "Black"
            width: 70
            height: 40

            TextInput
            {
                anchors.centerIn: parent
                text: idea.upLimit;
                font.pointSize: 10
                color: idea.upLimitEnabled ? "#f33c3c" : "#737373";
                selectByMouse: true
                validator: DoubleValidator{}
                onEditingFinished:
                {
                    idea.setUpLimit(text);
                }
            }
        }

        CheckBox
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -8
            text: "Enabled"

            checked: idea.upLimitEnabled;
            onCheckedChanged:
            {
                idea.setUpLimitEnabled(checked);
            }
        }
    }
}




