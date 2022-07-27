import QtQuick 2.0

Rectangle
{
    id: root
    color: "green"
    width: 10
    height: 10
    z: 2
    opacity: 0.9;

    property int finalX: 0
    property int finalY: 0


    SequentialAnimation
    {
        id: animation;
        ParallelAnimation
        {
            NumberAnimation
            {
                target: root
                property: "x"
                to: finalX;
                duration: 2400 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: root
                property: "y"
                to: finalY;
                duration: 2400 * idea.animationSpeed
                easing.type:  Easing.InQuad
            }
        }
        PauseAnimation
        {
            duration: 6700 * idea.animationSpeed
        }
        ScriptAction
        {
            script: root.destroy();
        }
    }
    function startAnimating()
    {
        animation.start();
    }
}
