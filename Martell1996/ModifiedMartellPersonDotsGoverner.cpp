#include "ModifiedMartellPersonDotsGoverner.h"

ModifiedMartellPersonDotsGoverner::ModifiedMartellPersonDotsGoverner()
{

}

void ModifiedMartellPersonDotsGoverner::setDotsArea(QQuickItem *dotsArea)
{
    m_dotsArea = dotsArea;
}

QQuickItem *ModifiedMartellPersonDotsGoverner::addDotFromPieChart(QColor color, int level, int positionInLevel)
{
    QQmlComponent newPersonDot(qmlEngine(m_dotsArea), QUrl(QStringLiteral("qrc:/QML/ModifiedMartellPersonDot.qml")));
    QObject * obj = newPersonDot.create(qmlEngine(m_dotsArea)->rootContext());
    QQuickItem * visibleObj = static_cast<QQuickItem*>(obj);
    visibleObj->setParent(m_dotsArea);
    visibleObj->setParentItem(m_dotsArea);
    visibleObj->setWidth(m_dotSizes.at(level));
    visibleObj->setHeight(m_dotSizes.at(level));
    visibleObj->setProperty("color", color);

    QPointF point = xyCoords(level, positionInLevel);

    QVariant xPos = QVariant(point.x());
    QVariant yPos = QVariant(point.y());
    QMetaObject::invokeMethod(visibleObj, "startCreationAnimation",
                              Q_ARG(QVariant, xPos),
                              Q_ARG(QVariant, yPos));
    return visibleObj;
}

QQuickItem *ModifiedMartellPersonDotsGoverner::addDot(QColor color, int level, int positionInLevel)
{
    QQmlComponent newPersonDot(qmlEngine(m_dotsArea), QUrl(QStringLiteral("qrc:/QML/ModifiedMartellPersonDot.qml")));
    QObject * obj = newPersonDot.create(qmlEngine(m_dotsArea)->rootContext());
    QQuickItem * visibleObj = static_cast<QQuickItem*>(obj);
    visibleObj->setParent(m_dotsArea);
    visibleObj->setParentItem(m_dotsArea);
    visibleObj->setWidth(m_dotSizes.at(level));
    visibleObj->setHeight(m_dotSizes.at(level));
    visibleObj->setProperty("color", color);

    QPointF point = xyCoords(level, positionInLevel);
    visibleObj->setPosition(point);

    return visibleObj;
}

QPointF ModifiedMartellPersonDotsGoverner::xyCoords(int level, int positionInLevel)
{
    return m_upLeftCoords.at(level) + QPointF(m_cellSizes.at(level).x() * (positionInLevel % m_numHorinzontal.at(level)),
                                              m_cellSizes.at(level).y() * qFloor(positionInLevel / m_numHorinzontal.at(level)))
            + QPointF(0.0, (m_cellSizes.at(level).y() - m_dotSizes.at(level)) / 2.0);
}

void ModifiedMartellPersonDotsGoverner::resize(int numLevels, QList<int> numberAtLevel)
{
    m_upLeftCoords.clear();
    m_upLeftCoords.reserve(numLevels);
    m_dotSizes.clear();
    m_dotSizes.reserve(numLevels);
    m_cellSizes.clear();
    m_cellSizes.reserve(numLevels);
    m_numHorinzontal.clear();
    m_numHorinzontal.reserve(numLevels);

    for(int i = 0; i < numLevels; i++)
    {
        double rectangleWidth = (180.0 + 360.0 * i / numLevels);
        double rectangleHeight = 360/numLevels - 2.0;

        double areaPerDot = rectangleHeight*rectangleWidth / numberAtLevel.at(i);
        int tryDotSize = qFloor(qSqrt(areaPerDot));

        int numVertical = qFloor(1.0 *rectangleHeight / tryDotSize);
        int numHorizontal = qCeil(1.0*numberAtLevel.at(i) / numVertical);
        while(numHorizontal * tryDotSize > rectangleWidth)
        {
            tryDotSize--;
            numVertical = qFloor(1.0*rectangleHeight / tryDotSize);
            numHorizontal = qCeil(1.0 * numberAtLevel.at(i) / numVertical);
        }
        double dotSize = tryDotSize;
        m_dotSizes.append(dotSize);
        m_numHorinzontal.append(numHorizontal);

        double extraVert = (rectangleHeight - numVertical * dotSize) / numVertical;
        double extraHoriz = (rectangleWidth - numHorizontal * dotSize) / numHorizontal;
        m_cellSizes.append(QPointF(extraHoriz + dotSize, extraVert + dotSize));

        m_upLeftCoords.append(QPointF(10.0 + 270.0 - rectangleWidth / 2.0 + extraHoriz / 2.0,
                                      50.0 + (rectangleHeight + 2.0) * i + extraVert / 2.0));
    }

}

double ModifiedMartellPersonDotsGoverner::getDotSize(int level)
{
    return m_dotSizes.at(level);
}

void ModifiedMartellPersonDotsGoverner::randomAttritionAnimation(QQuickItem *dot)
{
    QMetaObject::invokeMethod(dot, "startRandomAttritionAnimation");
    QTimer::singleShot(2100, dot, [dot]()
    {
        dot->deleteLater();
    });
}

void ModifiedMartellPersonDotsGoverner::positiveAttritionAnimation(QQuickItem *dot)
{
    QMetaObject::invokeMethod(dot, "startPositiveAttritionAnimation");
    QTimer::singleShot(2100, dot, [dot]()
    {
        dot->deleteLater();
    });
}

void ModifiedMartellPersonDotsGoverner::negativeAttritionAnimation(QQuickItem *dot)
{
    QMetaObject::invokeMethod(dot, "startNegativeAttritionAnimation");
    QTimer::singleShot(2100, dot, [dot]()
    {
        dot->deleteLater();
    });
}

void ModifiedMartellPersonDotsGoverner::promotionAnimateDot(QQuickItem *dot, int level, int positionInLevel)
{
    QPointF point = xyCoords(level, positionInLevel);

    double newSize = getDotSize(level);
    dot->setWidth(newSize);
    dot->setHeight(newSize);

    QVariant xPos = QVariant(point.x());
    QVariant yPos = QVariant(point.y());
    QMetaObject::invokeMethod(dot, "startPromotionAnimation",
                              Q_ARG(QVariant, xPos),
                              Q_ARG(QVariant, yPos));
}
