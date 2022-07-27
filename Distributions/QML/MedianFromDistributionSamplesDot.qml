import QtQuick 2.0

Rectangle
{
    id: root
    y: 20
    width: 4
    height: 4
    radius: 2
    opacity: 0.0
    color: Qt.rgba(1.0,0.4*Math.random(1)+0.3,0.4*Math.random(1)+0.3,1)

    property real dotFinalX: 0;
    property real delay1: 0;
    property real delay2: 0;

    SequentialAnimation
    {
        id: animation

        PauseAnimation
        {
            duration: 200*idea.animationSpeed
        }

        NumberAnimation
        {
            target: root
            property: "x"
            duration: 3000*idea.animationSpeed
            easing.type: Easing.Linear
            to: dotFinalX - 2
        }

        PauseAnimation
        {
            duration: delay1*idea.animationSpeed
        }

        NumberAnimation
        {
            target: root
            property: "opacity"
            to: 0;
            duration: 200*idea.animationSpeed
        }

        PauseAnimation
        {
            duration: delay2*idea.animationSpeed
        }

        ScriptAction
        {
            script: reset();
        }
    }

    function startAnimating(i, x, mean, delayFraction)
    {
        root.x = (i % 2) * 450
        root.opacity = 0.8;
        root.dotFinalX = x;

        root.delay1 = 4500 * delayFraction;
        root.delay2 = 4500 * (1 - delayFraction);

        animation.start();
    }
    function reset()
    {
        animation.stop();
        root.opacity = 0.0;
    }
}
