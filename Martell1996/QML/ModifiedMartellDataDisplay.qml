import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle
{
    width: 370
    height: 387
    color: "#cccccc"

    Rectangle
    {
        width: parent.width
        height: 3
        color: "black"
    }

    Row
    {
        x: 5
        y: 3
        height: 34
        Text
        {
            text: "Level"
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            width: 70
        }
        Label
        {
            text: "Incumbent's\nMean Score"
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            width: 100
            ToolTip.text: "Average plus or minus standard deviation"
            ToolTip.visible: meanScoreMouseArea.containsMouse;
            MouseArea
            {
                id: meanScoreMouseArea
                anchors.fill: parent
                hoverEnabled: true;
            }
        }
        Text
        {
            text: "Number\nof Positions"
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            width: 100
        }
        Text
        {
            text: "Percentage\nof Women";
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            width: 100
            ToolTip.text: "Average plus or minus standard deviation"
            ToolTip.visible: percentageWomenMouseArea.containsMouse;
            MouseArea
            {
                id: percentageWomenMouseArea
                anchors.fill: parent
                hoverEnabled: true;
            }
        }
    }

    Rectangle
    {
        y: 37
        width: parent.width
        height: 3
        color: "black"
    }

    ColumnLayout
    {
        y: 40
        width: 370
        height: 275
        ListView
        {
            id: levelListView;
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: dataModel
            spacing: 5

            ScrollBar.vertical: ScrollBar
            {
                width: 8
                anchors.right: levelListView.left
                policy: ScrollBar.AlwaysOn
            }

            delegate: Rectangle
            {
                width: 370
                height: 30
                color: "#ececec"
                Row
                {
                    anchors.fill: parent
                    Text
                    {
                        text: model.level
                        horizontalAlignment: Text.AlignHCenter
                        anchors.verticalCenter: parent.verticalCenter
                        width: 70
                    }
                    Text
                    {
                        text: model.meanScore.toFixed(2) + " &#177; " + model.meanScoreError.toFixed(2)
                        horizontalAlignment: Text.AlignHCenter
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        textFormat: Text.RichText;
                    }
                    Text
                    {
                        text: model.positions
                        horizontalAlignment: Text.AlignHCenter
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                    }
                    Text
                    {
                        text: model.percentWomen.toFixed(1) + " &#177; " + model.percentWomenError.toFixed(1)
                        horizontalAlignment: Text.AlignHCenter
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        textFormat: Text.RichText;
                    }
                }
            }
        }
    }

    Rectangle
    {
        y: 315
        width: parent.width
        color: "black"
        height: 10
    }

    Rectangle
    {
        y: 325
        height: 28
        color: "#ececec"
        width: parent.width
        Text
        {
            id: promotionCyclesText
            textFormat: Text.RichText;
            anchors.centerIn: parent;
            visible: idea.valid;
        }
        Connections
        {
            target: idea
            function onDisplayAveragePromotionCycles(cycles, stdev)
            {
                promotionCyclesText.text = "Average Promotion Cycles: " + cycles.toFixed(2) +
                        " &#177;" + stdev.toFixed(2);
            }
        }
    }
    Rectangle
    {
        y: 357
        height: 28
        color: "#ececec"
        width: parent.width
        Text
        {
            id: numberRunsText
            anchors.centerIn: parent;
            visible: idea.valid;
        }
        Connections
        {
            target: idea
            function onDisplayNumberRuns(runs)
            {
                numberRunsText.text = "Data from " + runs.toFixed(0) + " simulation runs.";
            }
        }
    }
}
