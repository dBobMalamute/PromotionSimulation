import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Shapes 1.12

import com.malamute.distributions 1.0

Item
{
    width: 580
    height: 424

    SamplerTemplate
    {

    }

    UpDownButton
    {
    }

    Item
    {
        id: distributionSamplesDotArea
        x: 55
        y: 10
        width: 450;
        height: 300;

        property int numSampleDots: 0;
        Component.onCompleted:
        {
            numSampleDots = idea.numPerSample;
            for(var i = 0; i < idea.numPerSample; i++)
            {
                var comp = Qt.createComponent("StdevFromDistributionSamplesDot.qml");
                var obj = comp.createObject(distributionSamplesDotArea,{x: 0});
            }
        }
        Connections
        {
            target: idea

            function onNumPerSampleChanged(numPerSample)
            {
                stdevAnimation.stop();
                for(var i = 0; i < distributionSamplesDotArea.numSampleDots; i++)
                {
                    distributionSamplesDotArea.children[i].reset();
                    distributionSamplesDotArea.children[i].destroy();
                }
                distributionSamplesDotArea.numSampleDots = numPerSample;

                for(i = 0; i < numPerSample; i++)
                {
                    var comp = Qt.createComponent("StdevFromDistributionSamplesDot.qml");
                    var obj = comp.createObject(distributionSamplesDotArea,{x: 0});
                }
            }
        }
    }

    Item
    {
        id: stdevDotsArea
        x: 55
        y: 10
        visible: idea.valid;
        width: 450
        height: 300

        property int numDotsShown: 0;
    }

    Item
    {
        id: stdevMeanBarsArea
        x: 55
        y: 10
        visible: idea.valid
        width: 450
        height: 300
    }

    Connections
    {
        target: idea
        function onStartAnimation()
        {
            if(idea.totalSamples > stdevDotsArea.numDotsShown)
            {
                stdevAnimation.start();
            }
        }

        function onResetAnimation()
        {
            stdevAnimation.stop();
            for(var i = 0; i < distributionSamplesDotArea.numSampleDots; i++)
            {
                distributionSamplesDotArea.children[i].reset();
            }

            for(var j = 0; j < stdevDotsArea.children.length; j++)
            {
                stdevDotsArea.children[j].destroy();
            }
            stdevDotsArea.numDotsShown = 0;

            for(var k = 0; k < stdevMeanBarsArea.children.length; k++)
            {
                stdevMeanBarsArea.children[k].destroy();
            }
        }
    }

    SequentialAnimation
    {
        id: stdevAnimation
        running: false
        loops: Animation.Infinite

        ScriptAction
        {
            script: nextSample();
        }

        PauseAnimation
        {
            duration: 15000 * idea.animationSpeed;
        }
    }

    function nextSample()
    {
        if(!idea.valid || stdevDotsArea.numDotsShown >= idea.totalSamples)
            stdevAnimation.stop();
        else
        {
            var dotPos = idea.getPositionsForDots(stdevDotsArea.numDotsShown);
            var meanPos = idea.getPositionForMeanLine(stdevDotsArea.numDotsShown);
            var stdevLength = idea.getStdevLineLength(stdevDotsArea.numDotsShown);

            for(var i = 0; i < distributionSamplesDotArea.numSampleDots; i++)
            {
                distributionSamplesDotArea.children[i].startAnimating(i, dotPos[i],
                                                                      stdevLength, meanPos);
            }

            var comp = Qt.createComponent("StdevFromDistributionSamplerBars.qml");
            var obj = comp.createObject(stdevMeanBarsArea,{x: meanPos - 1,
                                            stdevLength: stdevLength});
            obj.startAnimating();

            comp = Qt.createComponent("StdevFromDistributionStdevLine.qml");
            obj = comp.createObject(stdevDotsArea,{x: meanPos, y: 130,
                                        stdevLength: stdevLength,
                                        finalY: 295 - 2.0*stdevDotsArea.numDotsShown});
            obj.startAnimation();

            stdevDotsArea.numDotsShown++;
        }
    }
}
