#include "ModifiedMartellOrganizationLevel.h"
#include <QtMath>

ModifiedMartellOrganizationLevel::ModifiedMartellOrganizationLevel(ModifiedMartellParamsEtc *params, int level, QObject *parent) :
    QObject(parent),
    m_paramsEtc(params),
    m_level(level),
    m_numberPositions(1),
    m_positiveAttrition(0.0),
    m_randomAttrition(0.15),
    m_negativeAttrition(0.0)
{

}

ModifiedMartellOrganizationLevel::~ModifiedMartellOrganizationLevel()
{
    //qDeleteAll(m_persons);
}

int ModifiedMartellOrganizationLevel::positions() const
{
    return m_numberPositions;
}

void ModifiedMartellOrganizationLevel::setPositions(int positions)
{
    if (m_numberPositions == positions)
        return;

    m_numberPositions = positions;
}

int ModifiedMartellOrganizationLevel::sampleBinomial(double num, double prob)
{
    PoissonSampler sampler(num * prob);
    return static_cast<int>(sampler.getSamples(1).at(0));
}

void ModifiedMartellOrganizationLevel::setNegativeAttrition(double negativeAttrition)
{
    m_negativeAttrition = negativeAttrition;
}

void ModifiedMartellOrganizationLevel::setRandomAttrition(double randomAttrition)
{
    m_randomAttrition = randomAttrition;
}

void ModifiedMartellOrganizationLevel::setPositiveAttrition(double positiveAttrition)
{
    m_positiveAttrition = positiveAttrition;
}

void ModifiedMartellOrganizationLevel::reset(bool animate, bool updateDisplay)
{
    m_persons.clear();
    m_emptySlots.clear();

    if(!updateDisplay)
    {
        for(int i = 0; i < m_numberPositions; i++)
        {
            m_persons.push_back(m_paramsEtc->generatePerson(m_level, i, true));
        }
    }
    else if(!animate)
    {
        for(int i = 0; i < m_numberPositions; i++)
        {
            m_persons.push_back(m_paramsEtc->generatePerson(m_level, i, true));
            m_persons.at(i)->setupDot();
        }
    }
    else
    {
        for(int i = 0; i < m_numberPositions; i++)
        {
            m_persons.push_back(m_paramsEtc->generatePerson(m_level, i, true));
            m_persons.at(i)->setupDotAnimateIn();
        }
    }
}

void ModifiedMartellOrganizationLevel::attrition(bool animate)
{
    //Remove nullptrs from the list.
    m_persons.erase(std::remove(m_persons.begin(), m_persons.end(), nullptr), m_persons.end());

    // Sort the people to make positive, negative attrition faster.
    std::sort(m_persons.begin(), m_persons.end(), [](const std::unique_ptr<ModifiedMartellPerson> &person1,
              const std::unique_ptr<ModifiedMartellPerson> &person2)
    {
        return (person1->score() > person2->score());
    });
    int numVacancies = (m_numberPositions - m_persons.size());

    for(int i = 0; i < numVacancies; i++)
        m_persons.push_back(nullptr);

    if(!animate)
    {
        //Random Attrition
        for(int i = 0; i < m_numberPositions; i++)
        {
            double rand = QRandomGenerator::global()->generateDouble();
            if(rand < m_randomAttrition)
            {
                if(m_persons.at(i))
                {
                    m_emptySlots.push_back(m_persons.at(i)->positionInLevel());
                    m_persons[i].reset();
                }
            }
        }
        //Positive Attrition
        int numToRemove = sampleBinomial(positions(), m_positiveAttrition);
        int mostTalented = 0;
        for(int i = 0; i < numToRemove; i++)
        {
            while(mostTalented < m_numberPositions && !m_persons.at(mostTalented))
            {
                mostTalented++;

            }
            if(mostTalented == m_numberPositions)
            {
                return; // No people left to remove;
            }
            m_emptySlots.push_back(m_persons.at(mostTalented)->positionInLevel());
            m_persons[mostTalented].reset();
        }

        //Negative Attrition
        numToRemove = sampleBinomial(positions(), m_negativeAttrition);
        int leastTalented = m_numberPositions - 1;
        for(int i = 0; i < numToRemove; i++)
        {
            while(leastTalented > -1 && !m_persons.at(leastTalented))
            {
                leastTalented--;
            }
            if(leastTalented == -1)
                return; // No people left to remove;
            m_emptySlots.push_back(m_persons.at(leastTalented)->positionInLevel());
            m_persons[leastTalented].reset();
        }
    }
    else //Animate
    {
        //Random Attrition
        for(int i = 0; i < m_numberPositions; i++)
        {
            double rand = QRandomGenerator::global()->generateDouble();
            if(rand < m_randomAttrition)
            {
                if(m_persons.at(i))
                {
                    m_emptySlots.push_back(m_persons.at(i)->positionInLevel());
                    m_persons[i]->randomAttritionAnimation();
                    m_persons[i].reset();
                }
            }
        }
        //Positive Attrition
        int numToRemove = sampleBinomial(positions(), m_positiveAttrition);
        int mostTalented = 0;
        for(int i = 0; i < numToRemove; i++)
        {
            while(mostTalented < m_numberPositions && !m_persons.at(mostTalented))
            {
                mostTalented++;
            }
            if(mostTalented == m_numberPositions)
            {
                return; // No people left to remove;
            }
            m_emptySlots.push_back(m_persons.at(mostTalented)->positionInLevel());
            m_persons[mostTalented]->positiveAttritionAnimation();
            m_persons[mostTalented].reset();
        }

        //Negative Attrition
        numToRemove = sampleBinomial(positions(), m_negativeAttrition);
        int leastTalented = m_numberPositions - 1;
        for(int i = 0; i < numToRemove; i++)
        {
            while(leastTalented > -1 && !m_persons.at(leastTalented))
            {
                leastTalented--;
            }
            if(leastTalented == -1)
                return; // No people left to remove;
            m_emptySlots.push_back(m_persons.at(leastTalented)->positionInLevel());
            m_persons[leastTalented]->negativeAttritionAnimation();
            m_persons[leastTalented].reset();
        }
    }
}

int ModifiedMartellOrganizationLevel::numberEmptyPositions()
{
    return m_emptySlots.size();
}

std::vector<std::unique_ptr<ModifiedMartellPerson> > ModifiedMartellOrganizationLevel::promote(int n)
{
    std::vector<std::unique_ptr<ModifiedMartellPerson>> promotees;

    //People are ordered by talent. Best is 0.
    int mostTalented = 0;
    for(int i = 0; i < n; i++)
    {
        //Find the best person
        while(mostTalented < m_numberPositions && !m_persons.at(mostTalented))
        {
            mostTalented++;
        }
        if(mostTalented == m_numberPositions)
            return promotees;
        m_emptySlots.push_back(m_persons[mostTalented]->positionInLevel());
        promotees.push_back(std::move(m_persons[mostTalented]));
        m_persons[mostTalented] = nullptr;
        mostTalented++;
    }
    return promotees;
}

void ModifiedMartellOrganizationLevel::addPromoted(std::vector<std::unique_ptr<ModifiedMartellPerson>> newPersons, bool animate, bool updateDisplay)
{
    int j = 0;
    int leftToAdd = newPersons.size();
    if(leftToAdd == 0)
        return;

    if(!updateDisplay)
    {
        for(int i = 0; i < m_numberPositions; i++)
        {
            if(!m_persons.at(i))
            {
                leftToAdd--;
                m_persons[i] = std::move(newPersons[j]);
                m_persons[i]->setLevel(m_level);
                m_persons[i]->setPositionInLevel(m_emptySlots.back());
                m_emptySlots.pop_back();
                j++;

                if(leftToAdd == 0)
                    return;
            }
        }
    }
    else if(!animate)
    {
        for(int i = 0; i < m_numberPositions; i++)
        {
            if(!m_persons.at(i))
            {
                leftToAdd--;
                m_persons[i] = std::move(newPersons[j]);
                m_persons[i]->setLevel(m_level);
                m_persons[i]->setPositionInLevel(m_emptySlots.back());
                m_emptySlots.pop_back();
                m_persons[i]->moveDot();
                j++;

                if(leftToAdd == 0)
                    return;
            }
        }
    }
    else
    {
        for(int i = 0; i < m_numberPositions; i++)
        {
            if(!m_persons.at(i))
            {
                leftToAdd--;
                m_persons[i] = std::move(newPersons[j]);
                m_persons[i]->setLevel(m_level);
                m_persons[i]->setPositionInLevel(m_emptySlots.back());
                m_persons[i]->promotionAnimation();
                m_emptySlots.pop_back();
                j++;

                if(leftToAdd == 0)
                    return;
            }
        }
    }
}

void ModifiedMartellOrganizationLevel::addNewHires(bool animate, bool updateDisplay)
{
    if(!updateDisplay)
    {
        for(int i = 0; i < m_numberPositions; i++)
        {
            if(!m_persons.at(i))
            {
                m_persons[i] = m_paramsEtc->generatePerson(m_level, i, false);
                m_persons[i]->setPositionInLevel(m_emptySlots.back());
                m_emptySlots.pop_back();
            }
        }
    }
    else if(!animate)
    {
        for(int i = 0; i < m_numberPositions; i++)
        {
            if(!m_persons.at(i))
            {
                m_persons[i] = m_paramsEtc->generatePerson(m_level, i, false);
                m_persons[i]->setPositionInLevel(m_emptySlots.back());
                m_emptySlots.pop_back();
                m_persons[i]->setupDot();
            }
        }
    }
    else
    {
        for(int i = 0; i < m_numberPositions; i++)
        {
            if(!m_persons.at(i))
            {
                m_persons[i] = m_paramsEtc->generatePerson(m_level, m_emptySlots.back(), false);
                m_emptySlots.pop_back();
                m_persons[i]->setupDotAnimateIn();
            }
        }
    }
}

void ModifiedMartellOrganizationLevel::updateDisplay()
{
    for(size_t i = 0; i < m_persons.size(); i++)
    {
        if(m_persons.at(i))
            m_persons.at(i)->updateDot();
    }
}

double ModifiedMartellOrganizationLevel::percentWomen()
{
    if(m_persons.size() == 0 || m_numberPositions == 0)
        return NAN;

    int numWomen = 0;
    int numPeople = 0;

    for(int i = 0; i < m_numberPositions; i++)
    {
        if(m_persons.at(i) != nullptr)
        {
            numPeople++;
            if(m_persons.at(i)->gender() == SimulationGender::WOMEN)
                numWomen++;
        }
    }

    return 100.0 * numWomen / numPeople;
}

double ModifiedMartellOrganizationLevel::averageScore()
{
    if(m_persons.size() == 0 || m_numberPositions == 0)
        return NAN;

    double avgScore = 0.0;
    int numPeople = 0;
    for(int i = 0; i < m_numberPositions; i++)
    {
        if(m_persons.at(i) != nullptr)
        {
            numPeople++;
            avgScore += m_persons.at(i)->score();
        }
    }

    avgScore /= numPeople;
    return avgScore;
}

int ModifiedMartellOrganizationLevel::originalEmployees()
{
    if(m_persons.size() == 0 || m_numberPositions == 0)
        return NAN;

    int originals = 0;
    for(int i = 0; i < m_persons.size(); i++)
    {
        if(m_persons.at(i) != nullptr)
        {
            if(m_persons.at(i)->original())
                originals++;
        }
    }
    return originals;
}

