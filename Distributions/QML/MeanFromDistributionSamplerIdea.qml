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
        visible: true

        property int numSampleDots: 0;
        Component.onCompleted:
        {
            numSampleDots = idea.numPerSample;
            for(var i = 0; i < idea.numPerSample; i++)
            {
                var comp = Qt.createComponent("MeanFromDistributionSamplesDot.qml");
                var obj = comp.createObject(distributionSamplesDotArea,{x: i * 10});
            }
        }
        Connections
        {
            target: idea

            function onNumPerSampleChanged(numPerSample)
            {
                meanAnimation.stop();
                for(var i = 0; i < distributionSamplesDotArea.numSampleDots; i++)
                {
                    distributionSamplesDotArea.children[i].reset();
                    distributionSamplesDotArea.children[i].destroy();
                }
                distributionSamplesDotArea.numSampleDots = idea.numPerSample;

                for(i = 0; i < numPerSample; i++)
                {
                    var comp = Qt.createComponent("MeanFromDistributionSamplesDot.qml");
                    var obj = comp.createObject(distributionSamplesDotArea,{x: i * 10});
                }
                meanAnimation.start();
            }
        }
    }

    Item
    {
        id: meanDotsArea
        x: 55
        y: 10
        visible: idea.valid;
        width: 450
        height: 300

        property int numDotsShown: 0;
    }

    Item
    {
        id: meanBarArea
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
            if(idea.totalSamples > meanDotsArea.numDotsShown)
            {
                meanAnimation.start();
            }
        }

        function onResetAnimation()
        {
            meanAnimation.stop();
            for(var i = 0; i < distributionSamplesDotArea.numSampleDots; i++)
            {
                distributionSamplesDotArea.children[i].reset();
            }

            for(var j = 0; j < meanDotsArea.children.length; j++)
            {
                meanDotsArea.children[j].destroy();
            }
            meanDotsArea.numDotsShown = 0;

            for(var k = 0; k < meanBarArea.children.length; k++)
            {
                meanBarArea.children[k].destroy();
            }
        }
    }

    SequentialAnimation
    {
        id: meanAnimation
        running: false
        loops: Animation.Infinite

        ScriptAction
        {
            script: nextSample();
        }

        PauseAnimation
        {
            duration: 10200 * idea.animationSpeed;
        }
    }

    function nextSample()
    {
        if(!idea.valid || meanDotsArea.numDotsShown >= idea.totalSamples)
            meanAnimation.stop();
        else
        {
            var distSamplesPos = idea.getPositionsForMeanDots(meanDotsArea.numDotsShown);
            var meanPos = idea.getPositionForSampleDot(meanDotsArea.numDotsShown);

            if(meanPos.y > 5000)
            {
                return;
            }

            for(var i = 0; i < distributionSamplesDotArea.numSampleDots; i++)
            {
                distributionSamplesDotArea.children[i].startAnimating(i, distSamplesPos[i],
                                                                      15.0 + 55.0*i / idea.numPerSample, meanPos.x);
            }

            var comp = Qt.createComponent("MeanFromDistributionSamplerBar.qml");
            var obj = comp.createObject(meanBarArea,{x: meanPos.x - 1});
            obj.startAnimating();

            comp = Qt.createComponent("MeanFromDistributionMeanLine.qml");
            obj = comp.createObject(meanDotsArea,{x: meanDotsArea.numDotsShown % 2 * 450});
            obj.x = meanPos.x  - 1;
            obj.y = 100;
            obj.finalY = meanPos.y;
            obj.startAnimation();

            meanDotsArea.numDotsShown++;
        }
    }
}
