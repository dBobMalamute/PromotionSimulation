#ifndef MODIFIEDMARTELLPERSONDOTSGOVERNER_H
#define MODIFIEDMARTELLPERSONDOTSGOVERNER_H

#include <QQuickItem>
#include <QQmlEngine>
#include <QtMath>
#include <QMetaObject>
#include <QTimer>

class ModifiedMartellPersonDotsGoverner
{
public:
    ModifiedMartellPersonDotsGoverner();

    void setDotsArea(QQuickItem *dotsArea);

    QQuickItem* addDotFromPieChart(QColor color, int level, int positionInLevel);
    QQuickItem* addDot(QColor color, int level, int positionInLevel);
    QPointF xyCoords(int level, int positionInLevel);
    void resize(int numLevels, QList<int> numberAtLevel);
    double getDotSize(int level);

    void randomAttritionAnimation(QQuickItem* dot);
    void positiveAttritionAnimation(QQuickItem* dot);
    void negativeAttritionAnimation(QQuickItem* dot);
    void promotionAnimateDot(QQuickItem* dot, int level, int positionInLevel);

private:
    QQuickItem* m_dotsArea;

    QList<QPointF> m_upLeftCoords;
    QList<double> m_dotSizes;
    QList<QPointF> m_cellSizes;

    QList<int> m_numHorinzontal;
};

#endif // MODIFIEDMARTELLPERSONDOTSGOVERNER_H
