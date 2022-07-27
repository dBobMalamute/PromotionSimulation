import QtQuick 2.12
import QtQuick.Shapes 1.12

ShapePath
{
    id: root
    property alias startAngle: angleArc.startAngle;
    property alias sweepAngle: angleArc.sweepAngle;

    fillColor: "black"
    strokeColor: "transparent"
    strokeWidth: 0
    capStyle: ShapePath.FlatCap

    PathLine
    {
        x: pieChartShape.width / 2
        y: pieChartShape.height / 2
    }

    PathAngleArc
    {
        id: angleArc
        centerX: pieChartShape.width / 2; centerY: pieChartShape.height / 2
        radiusX: pieChartShape.width / 2; radiusY: pieChartShape.height / 2
        startAngle: 0
        sweepAngle: 120
    }

    PathLine
    {
        x: pieChartShape.width / 2
        y: pieChartShape.height / 2
    }
}
