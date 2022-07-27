#ifndef MODIFIEDMARTELLPERSON_H
#define MODIFIEDMARTELLPERSON_H

#include <QObject>
#include <QPointF>
#include <QColor>
#include "SimulationGender.h"
#include <QQuickItem>
#include "ModifiedMartellPersonDotsGoverner.h"

class ModifiedMartellPerson
{
public:
    ModifiedMartellPerson(QColor color, double score, bool original, SimulationGender::GENDER gender,
                          int level, int positionInLevel, ModifiedMartellPersonDotsGoverner* governer);

    ~ModifiedMartellPerson();

    QColor color() const;
    double score() const;
    bool original() const;
    SimulationGender::GENDER gender() const;

    void setupDot();
    void setupDotAnimateIn();
    void moveDot();
    void updateDot();

    void randomAttritionAnimation();
    void positiveAttritionAnimation();
    void negativeAttritionAnimation();
    void promotionAnimation();

    int level() const;
    void setLevel(int level);

    int positionInLevel() const;
    void setPositionInLevel(int positionInLevel);
    void deleteVisual();

private:
    QColor m_color;
    double m_score;
    bool m_original;
    SimulationGender::GENDER m_gender;

    int m_level;
    int m_positionInLevel;
    ModifiedMartellPersonDotsGoverner* m_governer;
    QQuickItem* m_visibleDot;
    bool dotMade = false;
    bool fadingOut = false;
};

#endif // MODIFIEDMARTELLPERSON_H
