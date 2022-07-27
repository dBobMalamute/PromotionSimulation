import QtQuick 2.12
import QtQuick.Controls 2.12

import com.malamute.distributions 1.0

DistributionDisplay
{
    Rectangle
    {
        id: dot
        width: 10
        height: 10
        radius: 10
        color: "red"
        opacity: 0.8
        y: 305 - (300 * (idea.modeDotHeight - idea.yLow) /
                  (idea.yHigh - idea.yLow))
        x: 50 + 450 * (idea.mode - idea.xLow) /
           (idea.xHigh - idea.xLow);
    }
    Rectangle
    {
        id: bar;
        x: dot.x + 4
        y: dot.y + 5
        width: 2
        height: 305-dot.y
        color: "red"
        opacity: 0.8
    }
    Rectangle
    {
        id: modeText

        width: modeWords.width + 4
        height: modeWords.height + 4
        x: dot.x + dot.width / 2- width/ 2
        y: dot.y + 20

        color: "black"
        border.width: 1
        border.color: "#1a1a1a"
        opacity: 1.0;
        Text
        {
            id: modeWords
            opacity: parent.opacity;
            anchors.centerIn: parent
            font.pointSize: 10
            font.bold: true

            text: "Mode: " + idea.mode.toPrecision(3);
            color: "#de1616"
        }
    }

}


