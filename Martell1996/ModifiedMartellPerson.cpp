#include "ModifiedMartellPerson.h"

ModifiedMartellPerson::ModifiedMartellPerson(QColor color, double score, bool original, SimulationGender::GENDER gender, int level, int positionInLevel, ModifiedMartellPersonDotsGoverner *governer) :
    m_color(color),
    m_score(score),
    m_original(original),
    m_gender(gender),
    m_level(level),
    m_positionInLevel(positionInLevel),
    m_governer(governer)
{

}

ModifiedMartellPerson::~ModifiedMartellPerson()
{
    if(dotMade && !fadingOut)
        m_visibleDot->deleteLater();
}

double ModifiedMartellPerson::score() const
{
    return m_score;
}

bool ModifiedMartellPerson::original() const
{
    return m_original;
}

SimulationGender::GENDER ModifiedMartellPerson::gender() const
{
    return m_gender;
}

void ModifiedMartellPerson::setupDot()
{
    dotMade = true;
    m_visibleDot = m_governer->addDot(m_color, m_level, m_positionInLevel);
}

void ModifiedMartellPerson::setupDotAnimateIn()
{
    dotMade = true;
    m_visibleDot = m_governer->addDotFromPieChart(m_color, m_level, m_positionInLevel);
}

void ModifiedMartellPerson::moveDot()
{
    m_visibleDot->setPosition(m_governer->xyCoords(m_level, m_positionInLevel));
    double newSize = m_governer->getDotSize(m_level);
    m_visibleDot->setWidth(newSize);
    m_visibleDot->setHeight(newSize);
}

void ModifiedMartellPerson::updateDot()
{
    if(dotMade)
        moveDot();
    else
        setupDot();
}

void ModifiedMartellPerson::randomAttritionAnimation()
{
    if(dotMade)
    {
        fadingOut = true;
        m_governer->randomAttritionAnimation(m_visibleDot);
    }
}

void ModifiedMartellPerson::positiveAttritionAnimation()
{
    if(dotMade)
    {
        fadingOut = true;
        m_governer->randomAttritionAnimation(m_visibleDot);
    }
}

void ModifiedMartellPerson::negativeAttritionAnimation()
{
    if(dotMade)
    {
        fadingOut = true;
        m_governer->randomAttritionAnimation(m_visibleDot);
    }
}

void ModifiedMartellPerson::promotionAnimation()
{
    if(dotMade)
    {
        m_governer->promotionAnimateDot(m_visibleDot, m_level, m_positionInLevel);
    }
}

int ModifiedMartellPerson::level() const
{
    return m_level;
}

void ModifiedMartellPerson::setLevel(int level)
{
    m_level = level;
}

int ModifiedMartellPerson::positionInLevel() const
{
    return m_positionInLevel;
}

void ModifiedMartellPerson::setPositionInLevel(int positionInLevel)
{
    m_positionInLevel = positionInLevel;
}

QColor ModifiedMartellPerson::color() const
{
    return m_color;
}

