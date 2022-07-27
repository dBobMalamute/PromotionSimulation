import QtQuick 2.0

Rectangle
{
    id: promotionRect
    color: "teal"
    width: 10
    height: 10
    z: 10
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
                target: promotionRect
                property: "x"
                to: finalX;
                duration: 2000 * idea.animationSpeed;
            }
            NumberAnimation
            {
                target: promotionRect
                property: "y"
                to: finalY;
                duration: 2000 * idea.animationSpeed;
            }
        }
        PauseAnimation
        {
            duration: 6100 * idea.animationSpeed;
        }
        ScriptAction
        {
            script: promotionRect.destroy();
        }
    }
    function startAnimating()
    {
        animation.start();
    }
}
