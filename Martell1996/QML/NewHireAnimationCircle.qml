import QtQuick 2.0

Rectangle
{
    id: root
    color: "green"
    width: 10
    height: 10
    z: 2
    opacity: 0.9;

    property int finalY: 0

    SequentialAnimation
    {
        id: animation;
        running: true
        NumberAnimation
        {
            target: root
            property: "y"
            to: finalY;
            duration: 3000 * idea.animationSpeed
            easing.type:  Easing.InQuad
        }
        PauseAnimation
        {
            duration: 1000 * idea.animationSpeed
        }
        ScriptAction
        {
            script: root.destroy();
        }
    }
}
