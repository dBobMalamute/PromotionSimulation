import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Shapes 1.12

import com.malamute.distributions 1.0

DistributionDisplay
{
    id: display

    Item
    {
        id: shapeAreaItem
        x: 55
        y: 10
        width: 450
        height: 300
        clip: true
        visible: idea.valid;

        Shape
        {
            anchors.fill: parent

            ShapePath
            {
                id: belowAreaShapePath
                fillColor:  "#45ff0000"
                strokeColor: "transparent"

                startX: 0;
                startY: 300;
            }
            ShapePath
            {
                id: aboveAreaShapePath
                fillColor:  "#4500ff00"
                strokeColor: "transparent"

                startX: 0;
                startY: 300;
            }
        }
    }

    Rectangle
    {
        id: dot
        visible: idea.valid
        width: 10
        height: 10
        radius: 10
        color: "red"
        opacity: 0.8
        y: 305 - (300 * (idea.medianDotHeight - idea.yLow) /
                  (idea.yHigh - idea.yLow))
        x: 50 + 450 * (idea.median - idea.xLow) /
           (idea.xHigh - idea.xLow);
    }
    Rectangle
    {
        id: bar;
        visible: idea.valid
        x: dot.x + 4
        y: dot.y + 5
        width: 2
        height: 305-dot.y
        color: "red"
        opacity: 0.8
    }
    Rectangle
    {
        id: medianText
        visible: idea.valid

        width: medianWordss.width + 4
        height: medianWordss.height + 4
        x: dot.x + dot.width / 2 - width / 2
        y: dot.y + 20

        color: "black"
        border.width: 1
        border.color: "#1a1a1a"
        opacity: 1.0;
        Text
        {
            id: medianWordss
            opacity: parent.opacity;
            anchors.centerIn: parent
            font.pointSize: 10
            font.bold: true

            text: "Median: " + idea.median.toPrecision(3);
            color: "#de1616"
        }
    }

    function clearArea()
    {
        // Empty the shape path.
        belowAreaShapePath.pathElements = [];
        aboveAreaShapePath.pathElements = [];
    }

    Connections
    {
        target: idea;

        function onDisplayAreas(xValuesBelow, yValuesBelow, xValuesAbove, yValuesAbove)
        {
            display.clearArea();

            //Start the shape path in the correct location.
            belowAreaShapePath.startX = xValuesBelow[0];
            belowAreaShapePath.startY = 301;

            //Start the shape path in the correct location.
            aboveAreaShapePath.startX = xValuesAbove[0];
            aboveAreaShapePath.startY = 301;

            var pathLine; var i;
            //Below
            for(i = 0; i < xValuesBelow.length; i++)
            {
                pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{x: " +
                                              xValuesBelow[i] + "; y: " + yValuesBelow[i] + "}",
                                              belowAreaShapePath);
                belowAreaShapePath.pathElements.push(pathLine);
            }

            pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{x: " +
                                          xValuesBelow[xValuesBelow.length - 1] + "; y: 301}",
                                          belowAreaShapePath);
            belowAreaShapePath.pathElements.push(pathLine);

            pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{x: " +
                                          xValuesBelow[0] + "; y: 301}",
                                          belowAreaShapePath);
            belowAreaShapePath.pathElements.push(pathLine);

            //Above
            for(i = 0; i < xValuesAbove.length; i++)
            {
                pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{x: " +
                                              xValuesAbove[i] + "; y: " + yValuesAbove[i] + "}",
                                              aboveAreaShapePath);
                aboveAreaShapePath.pathElements.push(pathLine);
            }

            pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{x: " +
                                          xValuesAbove[xValuesAbove.length - 1] + "; y: 301}",
                                          aboveAreaShapePath);
            aboveAreaShapePath.pathElements.push(pathLine);

            pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{x: " +
                                          xValuesAbove[0] + "; y: 301}",
                                          aboveAreaShapePath);
            aboveAreaShapePath.pathElements.push(pathLine);
        }
    }
}


