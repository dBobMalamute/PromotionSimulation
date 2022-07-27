import QtQuick 2.0

Rectangle
{
    id: root
    color: "white"
    width: 10
    height: 10
    opacity: 0.9;

    property int finalX: 0
    property int finalY: 0

    SequentialAnimation
    {
        id: animation;
        PauseAnimation
        {
            duration: 1000 * idea.animationSpeed;
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: root
                property: "x"
                to: finalX;
                duration: 2400 * idea.animationSpeed;
            }
            NumberAnimation
            {
                target: root
                property: "y"
                to: finalY;
                duration: 2400 * idea.animationSpeed;
                easing.type:  Easing.OutQuad
            }
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
