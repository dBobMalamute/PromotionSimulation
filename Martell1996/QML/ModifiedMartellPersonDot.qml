import QtQuick 2.12

Rectangle
{
    id: dot
    width: 10
    height: 10
    radius: 100
    color: "teal"

    property double xGoal: 0.0;
    property double yGoal: 0.0;

    function startCreationAnimation(xGoalInput, yGoalInput)
    {
        xGoal = xGoalInput;
        yGoal = yGoalInput;
        creationAnimation.start();
    }
    function startRandomAttritionAnimation()
    {
        randomAttritionAnimation.start();
    }
    function startPositiveAttritionAnimation()
    {
        randomPositiveAnimation.start();
    }
    function startNegativeAttritionAnimation()
    {
        randomNegativeAnimation.start();
    }
    function startPromotionAnimation(xGoalInput, yGoalInput)
    {
        xGoal = xGoalInput;
        yGoal = yGoalInput;
        promotionAnimation.start();
    }

    SequentialAnimation
    {
        id: creationAnimation
        running: false;
        ParallelAnimation
        {
            NumberAnimation
            {
                target: dot
                property: "y"
                to: yGoal + 20
                duration: 2000
                easing.type: Easing.OutQuad
            }
            NumberAnimation
            {
                target: dot
                property: "x"
                to: 0.1*xGoal;
                duration: 2000
            }
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: dot
                property: "y"
                to: yGoal
                duration: 2000
                easing.type: Easing.OutQuad
            }
            NumberAnimation
            {
                target: dot
                property: "x"
                to: xGoal
                duration: 2000
            }
        }
    }

    NumberAnimation
    {
        id: randomAttritionAnimation;
        running: false
        target: dot
        property: "opacity"
        to: 0.0;
        duration: 2000
    }

    NumberAnimation
    {
        id: positiveAttritionAnimation;
        running: false
        target: dot
        property: "opacity"
        to: 0.0;
        duration: 2000
    }

    NumberAnimation
    {
        id: negativeAttritionAnimation;
        running: false
        target: dot
        property: "opacity"
        to: 0.0;
        duration: 2000
    }

    SequentialAnimation
    {
        id: promotionAnimation
        NumberAnimation
        {
            target: dot
            property: "y"
            to: dot.y - 0.5 * width;
            duration: 200
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: dot
                property: "x"
                to: xGoal;
                duration: 1600
            }
            NumberAnimation
            {
                target: dot
                property: "y"
                to: yGoal + 0.5* width;
                duration: 1600
                easing.type: Easing.InOutQuad
            }
        }
        NumberAnimation
        {
            target: dot
            property: "y"
            to: yGoal;
            duration: 200
        }
    }
}
