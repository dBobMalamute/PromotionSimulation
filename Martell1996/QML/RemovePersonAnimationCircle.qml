import QtQuick 2.0

Rectangle
{
    id: root
    color: "white"
    width: 10
    height: 10
    radius: 10
    opacity: 0.7

    SequentialAnimation
    {
        running: true;
        NumberAnimation
        {
            target: root
            property: "opacity"
            to: 0
            duration: 2800 * idea.animationSpeed
        }
        ScriptAction
        {
            script: root.destroy();
        }
    }
}
