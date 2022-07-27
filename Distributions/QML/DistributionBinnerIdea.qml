import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Shapes 1.12

import com.malamute.distributions 1.0


Item
{
    width: 530
    height: 402

    DistributionDisplay
    {
        plotOpacity: 0.1
    }

    Item
    {
        id: boundsLineArea
        x: 55;
        y: 10;
        width: 450;
        height: 300
    }

    Item
    {
        id: barsArea
        x: 55;
        y: 10;
        width: 450
        height: 300
    }

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
            id: plotShape
            anchors.fill: parent
            visible: idea.valid;

            ShapePath
            {
                id: plotShapePath
                fillColor: "transparent"
                strokeColor: "#1de21d"
                strokeWidth: 2

                startX: 50;
                startY: 50;
            }
        }
    }

    Rectangle
    {
        id: discretePlotArea
        x: 55
        y: 10
        width: 450
        height: 300
        color: "transparent"
        clip: true
    }

    Connections
    {
        target: idea
        function onPlotContinuous(xValues, yValues, finalYValues)
        {
            clear();

            const xMin = idea.xLow
            const xMax = idea.xHigh;
            const xLength = xMax - xMin;

            const yMin = idea.yLow;
            const yMax = idea.yHigh;
            const yLength = yMax - yMin;

            var i;
            //Start the shape path in the correct location.
            plotShapePath.startX = xValues[0];
            plotShapePath.startY = yValues[0];
            for(i = 1; i < xValues.length; i++)
            {
                var pathComponent = Qt.createComponent("DistributionBinnerPathLine.qml");
                var pathLine = pathComponent.createObject(plotShapePath, {x: xValues[i], y: yValues[i]});

                pathLine.y = 300 - (300 * (finalYValues[i]));
                plotShapePath.pathElements.push(pathLine);
            }

            for(i = 0; i < idea.binBounds.length; i++)
            {
                var comp = Qt.createComponent("DistributionBinnerIdeaBoundsLine.qml");
                var obj = comp.createObject(boundsLineArea);
                obj.position = idea.getPositionForBoundLine(i);
                obj.startAnimating();
            }

            let heightFactor = 300 / idea.getBinDisplayHeight();
            for(i = 0; i < idea.binBounds.length + 1; i++)
            {
                comp = Qt.createComponent("DistributionBinnerIdeaBar.qml");
                obj = comp.createObject(barsArea,
                                        {x: idea.getPositionForBoundLine(i - 1) + 1,
                                        width: idea.getBinWidth(i),
                                        finalHeight: heightFactor * idea.getBinHeight(i),
                                        moreGreen: i % 2, i: i});
                obj.startAnimating();
            }
        }

        function onPlotDiscrete(xValues, yValues)
        {
//            clear();
//            const xMin = idea.gridBounds[0];
//            const xMax = idea.gridBounds[1];
//            const xLength = xMax - xMin;

//            const yMin = idea.gridBounds[2];
//            const yMax = idea.gridBounds[3];
//            const yLength = yMax - yMin;

//            var comp;
//            var obj;
//            for(var i = 0; i < xValues.length - 1; i++)
//            {
//                comp = Qt.createComponent("DistributionBinnerDiscreteDot.qml");
//                obj = comp.createObject(discretePlotArea,
//                                        {x: 450 * (xValues[i] - xMin) / xLength - 3,
//                                         y: (300 - (300 * (yValues[i] - yMin) / yLength) - 3)})
//                obj.startAnimating();
//            }
//            comp = Qt.createComponent("DistributionBinnerDiscreteDot.qml");
//            obj = comp.createObject(discretePlotArea,
//                                    {x: 450 * (xValues[i] - xMin) / xLength - 3,
//                                     y: (300 - (300 * (yValues[i] - yMin) / yLength) - 3)})
//            obj.startAnimating();

//            for(i = 0; i < idea.binBounds.length; i++)
//            {
//                comp = Qt.createComponent("DistributionBinnerIdeaBoundsLine.qml");
//                obj = comp.createObject(boundsLineArea);
//                obj.position = idea.getPositionForBoundLine(i);
//                obj.startAnimating();
//            }

//            for(i = 0; i < idea.binBounds.length + 1; i++)
//            {
//                comp = Qt.createComponent("DistributionBinnerIdeaBar.qml");
//                obj = comp.createObject(barsArea);
//                obj.x = idea.getPositionForBoundLine(i - 1) + 1;
//                obj.width = idea.getBinWidth(i);
//                obj.finalHeight = 300 * idea.getBinHeight(i) / (idea.gridBounds[3]-idea.gridBounds[2]);
//                obj.moreGreen = i % 2;
//                obj.i = i;
//                obj.startAnimating();
//            }
        }

        function clear()
        {
            plotShapePath.pathElements = [];

            var i;
            //Clear the bounds lines.
            for(i = 0; i < boundsLineArea.children.length; i++)
            {
                boundsLineArea.children[i].destroy();
            }

            //Clear the bars
            for(i = 0; i < barsArea.children.length; i++)
            {
                barsArea.children[i].destroy();
            }

            //Clear the discretePlotArea.
            for(i = 0; i < discretePlotArea.children.length; i++)
            {
                discretePlotArea.children[i].destroy();
            }
        }
    }

    Rectangle
    {
        width: parent.width
        height: 36
        anchors.bottom: controlRow.top
        anchors.bottomMargin: 3
        radius: 3

        gradient: Gradient
        {
            GradientStop{position: 0.0; color: "#101010"}
            GradientStop{position: 1.0; color: "#303030"}
        }

        clip: true

        ScrollView
        {
            anchors.fill: parent
            anchors.margins: 3

            TextInput
            {
                id: boundsInput
                anchors.fill: parent
                text: "0.00, 1.00, 2.00, 3.00, 4.00";
                font.pointSize: 10
                color: "#7c650d"
                Connections
                {
                    target: idea
                    function onBinBoundsChanged(bounds)
                    {
                        var boundsString = "" + bounds[0].toPrecision(3);
                        var i = 0;
                        for(i = 1; i < bounds.length; i++)
                        {
                            boundsString = boundsString.concat(", ");
                            boundsString = boundsString.concat(bounds[i].toPrecision(3));
                        }
                        boundsInput.text = boundsString;
                    }
                }
                onEditingFinished:
                {
                    idea.sanitizeInputBounds(text);
                }

                Component.onCompleted:
                {
                    var bounds = idea.binBounds;
                    var boundsString = "" + bounds[0].toPrecision(3);
                    var i = 0;
                    for(i = 1; i < bounds.length; i++)
                    {
                        boundsString = boundsString.concat(", ");
                        boundsString = boundsString.concat(bounds[i].toPrecision(3));
                    }
                    boundsInput.text = boundsString;
                }
            }
        }
    }


    Rectangle
    {
        id: controlRowBackground
        anchors.fill: controlRow
        anchors.rightMargin: -5
        anchors.leftMargin: -5
        radius: 3
        color: "#342b3b"
    }

    Row
    {
        id: controlRow
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        spacing: 3;

        Text
        {
            text: "Low: "
            font.bold: true
            font.pointSize: 10
            color: "#b5b5b5"
            anchors.verticalCenter: parent.verticalCenter
        }
        TextInput
        {
            id: lowTextInput
            text: idea.lowBinBoundary
            font.bold: true
            font.pointSize: 10
            color: "#b5b5b5"
            selectByMouse: true;
            validator: DoubleValidator{decimals: 3}
            anchors.verticalCenter: parent.verticalCenter
            onEditingFinished:
            {
                idea.setLowBinBoundary(text);
            }
        }

        Rectangle
        {
            id: spacer
            width: 10
            height: 10
            color: "transparent"
        }

        Text
        {
            text: "Up: ";
            font.bold: true
            font.pointSize: 10
            color: "#b5b5b5"
            anchors.verticalCenter: parent.verticalCenter
        }
        TextInput
        {
            id: upTextInput
            text: idea.upBinBoundary
            font.bold: true
            font.pointSize: 10
            color: "#b5b5b5"
            validator: DoubleValidator{decimals: 3}
            anchors.verticalCenter: parent.verticalCenter
            selectByMouse: true;
            onEditingFinished:
            {
                idea.setUpBinBoundary(text);
            }
        }

        Rectangle
        {
            id: spacer2
            width: 10
            height: 10
            color: "transparent"
        }

        Text
        {
            text: "#: "
            font.bold: true
            font.pointSize: 10
            color: "#b5b5b5"
            anchors.verticalCenter: parent.verticalCenter
        }
        TextInput
        {
            text: idea.numBins
            font.bold: true
            font.pointSize: 10
            color: "#b5b5b5"
            validator: IntValidator{bottom: 2; top: 99}
            selectByMouse: true;
            anchors.verticalCenter: parent.verticalCenter
            onEditingFinished:
            {
                idea.setNumBins(text);
            }
        }

        Rectangle
        {
            id: spacer3
            width: 10
            height: 10
            color: "transparent"
        }

        Button
        {
            text: "Set";
            height: 30
            width: 40
            enabled: idea.upBinBoundary > idea.lowBinBoundary
            onClicked:
            {
                idea.setBoundsByButton();
            }
        }

        Rectangle
        {
            width: 50
            height: 10
            color: "transparent"
        }

        Button
        {
            text: "Replay"
            height: 30
            width: 80
            onClicked:
            {
                idea.replay();
            }
        }
    }
}
