#include "ModifiedMartellIdea.h"
#include <QJsonArray>
#include <QQmlEngine>
#include <QFile>
#include <QDir>

ModifiedMartellAttributes::ModifiedMartellAttributes()
{
    m_listName = "Modified Martell Simulation";
    m_displayName = "Modified Martell Simulation";
    m_authors << "dBob";
    m_description = "This runs and presents a modified version of the 1996 Martell Simulation.";
    m_iconPath =  "qrc:/Icons/ModifiedMartellSimulation.png";

    m_dataTypesIn << Magic<ModifiedMartellGroupDataTypeAttributes>::cast().id() << Magic<ModifiedMartellGroupDataTypeAttributes>::cast().id()
                  << Magic<ModifiedMartellGroupDataTypeAttributes>::cast().id() << Magic<ModifiedMartellGroupDataTypeAttributes>::cast().id()
                  << Magic<ModifiedMartellGroupDataTypeAttributes>::cast().id() << Magic<ModifiedMartellGroupDataTypeAttributes>::cast().id();

    m_labelsIn << "" << "" << "" << "" << "" << "";

    m_dataTypesOut << Magic<ModifiedMartellDataTypeAttributes>::cast().id();
    m_labelsOut << "data";
    m_customLabels = true;

    m_embeddedQMLPath = ":/QML/ModifiedMartell.qml";

    m_externalQMLPaths << ":/QML/ModifiedMartellPyramidSetup.qml";
    m_externalQMLLocations.append({false, false, 10,-420});
    m_externalQMLPaths << ":/QML/Martell1996Controls.qml";
    m_externalQMLLocations.append({false, true, 10,10});

    m_externalQMLPaths << ":/QML/Martell1996Controls2.qml";
    m_externalQMLLocations.append({false, true, 300,10});
    m_externalQMLPaths << ":/QML/Martell1996Controls3.qml";
    m_externalQMLLocations.append({false, true, 500,10});


    m_gear = true;

    qmlRegisterType(QUrl("qrc:/QML/ModifiedMartellPieChartPath.qml"), "com.martell1996.extras", 1, 0, "ModifiedMartellPieChartPath");
    qmlRegisterType(QUrl("qrc:/QML/ModifiedMartellPieChartKey.qml"), "com.martell1996.extras", 1, 0, "ModifiedMartellPieChartKey");
    qmlRegisterType(QUrl("qrc:/QML/ModifiedMartellPyramidLevel.qml"), "com.martell1996.extras", 1, 0, "ModifiedMartellPyramidLevel");
    qmlRegisterUncreatableType<SimulationMode>("com.martell1996.extras", 1, 0, "SimulationMode",
                                               "Cannot create a simulation mode object. This is an enum");
}

const IdeaAttributes ModifiedMartellIdea::attributes()
{
    return Magic<ModifiedMartellAttributes>::cast();
}

ModifiedMartellIdea::ModifiedMartellIdea() :
    m_originals(0),
    m_bulkRunNum(20),
    m_mode(SimulationMode::NORMAL),
    m_numLevels(8),
    m_stopAtNoOriginals(true),
    m_cyclesToStopAt(20)
{
    m_paramsEtc = new ModifiedMartellParamsEtc();
    m_paramsEtc->setGoverner(&m_dotsGoverner);

    //Setup Positions at level
    m_positionsAtLevel.reserve(30);
    m_positionsAtLevel << 10 << 40 << 75 << 100 << 150 << 200 << 300 << 500;
    for (int i = 0; i < 22; i++)
        m_positionsAtLevel.append(500 + 10*i);

    m_dotsGoverner.resize(8, m_positionsAtLevel);

    //Setup attrition rates.
    m_positiveAttrition.reserve(30);
    m_randomAttrition.reserve(30);
    m_negativeAttrition.reserve(30);
    for (int i = 0; i < 30; i++)
    {
        m_positiveAttrition.append(0.0);
        m_randomAttrition.append(0.15);
        m_negativeAttrition.append(0.0);
    }

    for(int i = 0; i < 30; i++)
    {
        m_levels.append(new ModifiedMartellOrganizationLevel(m_paramsEtc, i, this));
    }
}

void ModifiedMartellIdea::finishSetupQmlContext()
{
    setup();
}

ModifiedMartellIdea::~ModifiedMartellIdea()
{
    qDeleteAll(m_levels);
}

void ModifiedMartellIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber)
{
    auto input = std::dynamic_pointer_cast<ModifiedMartellGroupDataType>(dataType);

    if(plugNumber == 0)
        m_group1 = input;
    else if(plugNumber == 1)
        m_group2 = input;
    else if(plugNumber == 2)
        m_group3 = input;
    else if(plugNumber == 3)
        m_group4 = input;
    else if(plugNumber == 4)
        m_group5 = input;
    else if(plugNumber == 5)
        m_group6 = input;

    validate();
}

std::shared_ptr<DataType> ModifiedMartellIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_dataOut);
}

QJsonObject ModifiedMartellIdea::save() const
{
    QJsonObject saveJson = Idea::save();
    saveJson["n"] = m_numLevels;

    QJsonArray positionsAtLevelArray;
    for(int i = 0; i < 30; i++)
    {
        positionsAtLevelArray.append(m_positionsAtLevel.at(i));
    }
    saveJson["pAtL"] = positionsAtLevelArray;

    QJsonArray positiveAttritionArray;
    QJsonArray randomAttritionArray;
    QJsonArray negativeAttritionArray;

    for(int i = 0; i < 30; i++)
    {
        positiveAttritionArray.append(m_positiveAttrition.at(i));
        randomAttritionArray.append(m_randomAttrition.at(i));
        negativeAttritionArray.append(m_negativeAttrition.at(i));
    }
    saveJson["apAtL"] = positiveAttritionArray;
    saveJson["arAtL"] = randomAttritionArray;
    saveJson["anAtL"] = negativeAttritionArray;

    saveJson["b"] = m_bulkRunNum;
    saveJson["os"] = m_stopAtNoOriginals;
    saveJson["sc"] = m_cyclesToStopAt;

    return saveJson;
}

void ModifiedMartellIdea::load(const QJsonObject &obj)
{
    QJsonValue v = obj["n"];
    if(!v.isUndefined())
    {
        m_numLevels = v.toInt();
        emit numLevelsChanged(m_numLevels);
    }

    v = obj["pAtL"];
    if(!v.isUndefined())
    {
        m_positionsAtLevel.clear();
        m_positionsAtLevel.reserve(30);
        QJsonArray positionsAtLevelArray = v.toArray();
        for(int i = 0; i < 30; i++)
            m_positionsAtLevel.append(positionsAtLevelArray.at(i).toInt());

        emit positionsAtLevelChanged(m_positionsAtLevel);
    }

    v = obj["apAtL"];
    if(!v.isUndefined())
    {
        m_positiveAttrition.clear();
        m_positiveAttrition.reserve(30);
        QJsonArray attritionArray = v.toArray();
        for(int i = 0; i < 30; i++)
        {
            m_positiveAttrition.append(attritionArray.at(i).toDouble());
            m_levels.at(i)->setPositiveAttrition(m_positiveAttrition.at(i));
        }
        emit positiveAttritionChanged(m_positiveAttrition);
    }

    v = obj["arAtL"];
    if(!v.isUndefined())
    {
        m_randomAttrition.clear();
        m_randomAttrition.reserve(30);
        QJsonArray attritionArray = v.toArray();
        for(int i = 0; i < 30; i++)
        {
            m_randomAttrition.append(attritionArray.at(i).toDouble());
            m_levels.at(i)->setRandomAttrition(m_randomAttrition.at(i));
        }
        emit randomAttritionChanged(m_randomAttrition);
    }

    v = obj["anAtL"];
    if(!v.isUndefined())
    {
        m_negativeAttrition.clear();
        m_negativeAttrition.reserve(30);
        QJsonArray attritionArray = v.toArray();
        for(int i = 0; i < 30; i++)
        {
            m_negativeAttrition.append(attritionArray.at(i).toDouble());
            m_levels.at(i)->setNegativeAttrition(m_negativeAttrition.at(i));
        }
        emit negativeAttritionChanged(m_negativeAttrition);
    }

    v = obj["b"];
    if(!v.isUndefined())
    {
        m_bulkRunNum = v.toInt();
        emit bulkRunNumChanged(m_bulkRunNum);
    }

    v = obj["os"];
    if(!v.isUndefined())
    {
        m_stopAtNoOriginals = v.toBool();
        emit stopAtNoOriginalsChanged(m_stopAtNoOriginals);
    }

    v = obj["sc"];
    if(!v.isUndefined())
    {
        m_cyclesToStopAt = v.toInt();
        emit cyclesToStopAtChanged(m_cyclesToStopAt);
    }

    setup();
}

int ModifiedMartellIdea::numLevels() const
{
    return m_numLevels;
}

QList<int> ModifiedMartellIdea::positionsAtLevel() const
{
    return m_positionsAtLevel;
}

QList<double> ModifiedMartellIdea::positiveAttrition() const
{
    return m_positiveAttrition;
}

QList<double> ModifiedMartellIdea::randomAttrition() const
{
    return m_randomAttrition;
}

QList<double> ModifiedMartellIdea::negativeAttrition() const
{
    return m_negativeAttrition;
}

bool ModifiedMartellIdea::stopAtNoOriginals() const
{
    return m_stopAtNoOriginals;
}

int ModifiedMartellIdea::cyclesToStopAt() const
{
    return m_cyclesToStopAt;
}

QList<QVariant> ModifiedMartellIdea::percentWomen() const
{
    return m_percentWomen;
}

QList<QVariant> ModifiedMartellIdea::meanScore() const
{
    return m_meanScore;
}

int ModifiedMartellIdea::originals() const
{
    return m_originals;
}

int ModifiedMartellIdea::promotionCycles() const
{
    return m_promotionCycles;
}

int ModifiedMartellIdea::bulkRunNum() const
{
    return m_bulkRunNum;
}

SimulationMode::SimulationModeEnum ModifiedMartellIdea::mode() const
{
    return m_mode;
}

void ModifiedMartellIdea::validate()
{
    auto v_group1 = m_group1.lock();
    auto v_group2 = m_group2.lock();
    auto v_group3 = m_group3.lock();
    auto v_group4 = m_group4.lock();
    auto v_group5 = m_group5.lock();
    auto v_group6 = m_group6.lock();

    if(!v_group1 && !v_group2 && !v_group3 && !v_group4 && !v_group5 && !v_group6)
    {
        emit hideCohensD();
        setDefaultStatus();
    }
    else
    {
        m_paramsEtc->resetGroups();

        if(v_group1 && !qFuzzyCompare(v_group1->groupPercentage(), 0.0))
        {
            m_paramsEtc->addGroup(v_group1);
        }
        if(v_group2 && !qFuzzyCompare(v_group2->groupPercentage(), 0.0))
        {
            m_paramsEtc->addGroup(v_group2);
        }
        if(v_group3 && !qFuzzyCompare(v_group3->groupPercentage(), 0.0))
        {
            m_paramsEtc->addGroup(v_group3);
        }
        if(v_group4 && !qFuzzyCompare(v_group4->groupPercentage(), 0.0))
        {
            m_paramsEtc->addGroup(v_group4);
        }
        if(v_group5 && !qFuzzyCompare(v_group5->groupPercentage(), 0.0))
        {
            m_paramsEtc->addGroup(v_group5);
        }
        if(v_group6 && !qFuzzyCompare(v_group6->groupPercentage(), 0.0))
        {
            m_paramsEtc->addGroup(v_group6);
        }

        if(m_paramsEtc->getNumGroups() == 0)
        {
            setStatus(IdeaStatus::Error, "All percentages 0%", "If all the percentages are set to 0, there are no people");
        }
        else if(!m_paramsEtc->setupCumulativePercentages())
        {
            setStatus(IdeaStatus::Error, "Total percentage is not 100%.", "The total percentage is not 100%");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Ready", "This box has the data required to simulate.");
            calculateCohensD();
            emit setupPieChart(m_paramsEtc->getNumGroups(), m_paramsEtc->getPieChartSweeps(), m_paramsEtc->getGroupColors());
            emit setupNameRectangles(m_paramsEtc->getNumGroups(), m_paramsEtc->getGroupNames(), m_paramsEtc->getGroupColors());
            reset();
        }
    }


    m_dataOut = std::make_shared<ModifiedMartellDataType>();
    emit newData(0);
}

void ModifiedMartellIdea::calculateCohensD()
{
    double d;
    if(m_paramsEtc->calculateCohensD(d))
    {
        emit showCohensD(d);
    }
    else
    {
        emit hideCohensD();
    }
}

void ModifiedMartellIdea::setPositiveAttrition(int level, double attritionRate)
{
    if(qFuzzyCompare(m_positiveAttrition.at(level), attritionRate))
        return;

    m_positiveAttrition[level] = attritionRate;
    m_levels.at(level)->setPositiveAttrition(attritionRate);
    emit positiveAttritionChanged(m_positiveAttrition);
}

void ModifiedMartellIdea::setRandomAttrition(int level, double attritionRate)
{
    if(qFuzzyCompare(m_randomAttrition.at(level), attritionRate))
        return;

    m_randomAttrition[level] = attritionRate;
    m_levels.at(level)->setRandomAttrition(attritionRate);
    emit randomAttritionChanged(m_randomAttrition);
}

void ModifiedMartellIdea::setNegativeAttrition(int level, double attritionRate)
{
    if(qFuzzyCompare(m_negativeAttrition.at(level), attritionRate))
        return;

    m_negativeAttrition[level] = attritionRate;
    m_levels.at(level)->setNegativeAttrition(attritionRate);
    emit negativeAttritionChanged(m_negativeAttrition);
}

void ModifiedMartellIdea::setupPersonDotsArea(QQuickItem *item)
{
    m_dotsGoverner.setDotsArea(item);
}

void ModifiedMartellIdea::setStopAtNoOriginals(bool stopAtNoOriginals)
{
    if (m_stopAtNoOriginals == stopAtNoOriginals)
        return;

    m_stopAtNoOriginals = stopAtNoOriginals;
    emit stopAtNoOriginalsChanged(m_stopAtNoOriginals);
}

void ModifiedMartellIdea::setCyclesToStopAt(int cyclesToStopAt)
{
    if (m_cyclesToStopAt == cyclesToStopAt)
        return;

    m_cyclesToStopAt = cyclesToStopAt;
    emit cyclesToStopAtChanged(m_cyclesToStopAt);
}

void ModifiedMartellIdea::setNumLevels(int numLevels)
{
    if (m_numLevels == numLevels)
        return;

    QJsonObject oldParams;
    oldParams["n"] = m_numLevels;

    m_numLevels = numLevels;
    emit numLevelsChanged(m_numLevels);

    QJsonObject newParams;
    newParams["n"] = m_numLevels;
    reportParamsChanged(oldParams, newParams);

    setup();
}

void ModifiedMartellIdea::setPositionAtOneLevel(int level, int positions)
{
    if(m_positionsAtLevel.at(level) == positions)
        return;

    m_positionsAtLevel[level] = positions;
    emit positionsAtLevelChanged(m_positionsAtLevel);

    setup();
}

void ModifiedMartellIdea::setPositionsAtLevel(QList<int> positionsAtLevel)
{
    if (m_positionsAtLevel == positionsAtLevel)
        return;

    m_positionsAtLevel = positionsAtLevel;
    emit positionsAtLevelChanged(m_positionsAtLevel);

    setup();
}

void ModifiedMartellIdea::normalStepButtonClicked()
{
    if(m_mode == SimulationMode::ANIMATE)
    {
        if(nextAction == PromoteFromWithinStart)
        {
            for(int i = 0; i < m_numLevels - 1; i++)
            {
                int emptyPos = m_levels[i]->numberEmptyPositions();
                m_levels[i]->addPromoted(m_levels[i+1]->promote(emptyPos), false, true);
            }

            m_levels[m_numLevels - 1]->addNewHires(false, true);
        }
        else if(nextAction == NewHiresStart)
        {
            m_levels[m_numLevels - 1]->addNewHires(false, true);
        }
    }

    setMode(SimulationMode::NORMAL);
    emit startSpinningGear();

    normalStep(true);
    updateStatistics();

    emit stopSpinningGear();
}

void ModifiedMartellIdea::normalFinishButtonClicked()
{
    if(m_mode == SimulationMode::ANIMATE)
    {
        if(nextAction == PromoteFromWithinStart)
        {
            for(int i = 0; i < m_numLevels - 1; i++)
            {
                int emptyPos = m_levels[i]->numberEmptyPositions();
                m_levels[i]->addPromoted(m_levels[i+1]->promote(emptyPos), false, true);
            }

            m_levels[m_numLevels - 1]->addNewHires(false, true);
        }
        else if(nextAction == NewHiresStart)
        {
            m_levels[m_numLevels - 1]->addNewHires(false, true);
        }
    }

    setMode(SimulationMode::NORMAL);
    emit startSpinningGear();

    if(m_stopAtNoOriginals)
    {
        int originals = m_originals;
        while(originals != 0)
        {
            normalStep(false);

            int totalOriginals = 0;
            for(int i = 0; i < m_numLevels; i++)
            {
                totalOriginals += m_levels.at(i)->originalEmployees();
            }
            originals = totalOriginals;
        }
    }
    else
    {
        for(int i = 0; i < m_cyclesToStopAt; i++)
            normalStep(false);
    }

    updateStatistics();

    for(int i = 0; i < m_numLevels; i++)
        m_levels.at(i)->updateDisplay();

    emit stopSpinningGear();
}

void ModifiedMartellIdea::normalResetButtonClicked()
{
    setMode(SimulationMode::NORMAL);

    reset();
}

void ModifiedMartellIdea::normalStep(bool updateDisplay)
{
    //Attrition.
    for(int i = 0; i < m_numLevels; i++)
    {
        m_levels[i]->attrition(false);
    }

    for(int i = 0; i < m_numLevels - 1; i++)
    {
        int emptyPos = m_levels[i]->numberEmptyPositions();
        m_levels[i]->addPromoted(m_levels[i+1]->promote(emptyPos), false, updateDisplay);
    }

    m_levels[m_numLevels - 1]->addNewHires(false, updateDisplay);

    setPromotionCycles(m_promotionCycles + 1);
}

void ModifiedMartellIdea::setup()
{
    for(int i = 0; i < m_numLevels; i++)
        m_levels[i]->setPositions(m_positionsAtLevel.at(i));

    m_dotsGoverner.resize(m_numLevels, m_positionsAtLevel);

    if(valid())
        reset();
}

void ModifiedMartellIdea::reset(bool animate, bool updateDisplay)
{
    setPromotionCycles(0);

    for(int i = 0; i < m_numLevels; i++)
        m_levels[i]->reset(animate, updateDisplay);

    updateStatistics();
}

void ModifiedMartellIdea::animationStepButtonClicked()
{
    setMode(SimulationMode::ANIMATE);
    nextActionFromTimer();
}

void ModifiedMartellIdea::animationResetButtonClicked()
{
    setMode(SimulationMode::ANIMATE);
    nextAction = AttritionStart;
    reset(true);
}

void ModifiedMartellIdea::bulkRun()
{
    startSpinningGear();

    setMode(SimulationMode::BULK);

    //Start gear. Clear old data.
    m_bulkRunData.clear();
    m_bulkRunData.reserve(m_bulkRunNum);

    for(int i = 0; i < m_bulkRunNum; i++)
    {
        //Reset for simulation run.
        reset(false, false);

        //Run the simulation.
        if(m_stopAtNoOriginals)
        {
            double originals = m_originals;
            while(originals != 0)
            {
                normalStep(false);

                int totalOriginals = 0;
                for(int i = 0; i < m_numLevels; i++)
                {
                    totalOriginals += m_levels.at(i)->originalEmployees();
                }
                originals = totalOriginals;
            }
        }
        else
        {
            for(int i = 0; i < m_cyclesToStopAt; i++)
                normalStep(false);
        }

        updateStatistics();
        QList<double> percentWomen;
        QList<double> meanScore;
        for(int i = 0; i < m_numLevels; i++)
        {
            percentWomen.append(m_percentWomen.at(i).toDouble());
            meanScore.append(m_meanScore.at(i).toDouble());
        }
        runData data = runData(percentWomen, meanScore, m_promotionCycles);
        m_bulkRunData.append(data);
    }

    for(int i = 0; i < m_numLevels; i++)
        m_levels.at(i)->updateDisplay();

    //Export data stop gear.
    m_dataOut = std::make_shared<ModifiedMartellDataType>(m_bulkRunNum, m_positionsAtLevel, m_bulkRunData);
    emit newData(0);

    stopSpinningGear();
}

void ModifiedMartellIdea::attritionStep()
{
    for(int i = 0; i < m_numLevels; i++)
    {
        m_levels[i]->attrition(true);
    }
}

void ModifiedMartellIdea::promoteFromWithin()
{
    for(int i = 0; i < m_numLevels - 1; i++)
    {
        int emptyPos = m_levels[i]->numberEmptyPositions();
        m_levels[i]->addPromoted(m_levels[i+1]->promote(emptyPos), true, true);
    }
}

void ModifiedMartellIdea::fillLowestLevelNewHires()
{
    m_levels[m_numLevels - 1]->addNewHires(true);

    setPromotionCycles(m_promotionCycles + 1);
    updateStatistics();
}

void ModifiedMartellIdea::bulkRunButtonClicked()
{
    bulkRun();
}

void ModifiedMartellIdea::nextActionFromTimer()
{
    if(nextAction == AttritionStart)
    {
        attritionStep();
        nextAction = PromoteFromWithinStart;
    }
    else if(nextAction == PromoteFromWithinStart)
    {
        promoteFromWithin();
        nextAction = NewHiresStart;
    }
    else if(nextAction == NewHiresStart)
    {
        fillLowestLevelNewHires();
        nextAction = AttritionStart;
    }
}

void ModifiedMartellIdea::setPercentWomen(QList<QVariant> percentWomen)
{
    if (m_percentWomen == percentWomen)
        return;

    m_percentWomen = percentWomen;
    emit percentWomenChanged(m_percentWomen);
}

void ModifiedMartellIdea::setMeanScore(QList<QVariant> meanScore)
{
    if (m_meanScore == meanScore)
        return;

    m_meanScore = meanScore;
    emit meanScoreChanged(m_meanScore);
}

void ModifiedMartellIdea::setOriginals(int originals)
{
    if (m_originals == originals)
        return;

    m_originals = originals;
    emit originalsChanged(m_originals);
}

void ModifiedMartellIdea::setPromotionCycles(int promotionCycles)
{
    if (m_promotionCycles == promotionCycles)
        return;

    m_promotionCycles = promotionCycles;
    emit promotionCyclesChanged(m_promotionCycles);
}

void ModifiedMartellIdea::setBulkRunNum(int bulkRunNum)
{
    if (m_bulkRunNum == bulkRunNum)
        return;

    m_bulkRunNum = bulkRunNum;
    emit bulkRunNumChanged(m_bulkRunNum);
}

void ModifiedMartellIdea::setMode(SimulationMode::SimulationModeEnum mode)
{
    if (m_mode == mode)
        return;

    if(m_mode == SimulationMode::ANIMATE)
    {
        if(nextAction == PromoteFromWithinStart)
        {
            promoteFromWithin();
            fillLowestLevelNewHires();
        }
        if(nextAction == NewHiresStart)
            fillLowestLevelNewHires();
    }

    m_mode = mode;
    emit modeChanged(m_mode);
}

void ModifiedMartellIdea::updateStatistics()
{
    QList<QVariant> percentWomen;
    percentWomen.reserve(m_numLevels);
    for(int i = 0; i < m_numLevels; i++)
    {
        percentWomen.append(m_levels.at(i)->percentWomen());
    }
    setPercentWomen(percentWomen);

    QList<QVariant> averageScore;
    averageScore.reserve(m_numLevels);
    for(int i = 0; i < m_numLevels; i++)
    {
        averageScore.append(m_levels.at(i)->averageScore());
    }
    setMeanScore(averageScore);

    int totalOriginals = 0;
    for(int i = 0; i < m_numLevels; i++)
    {
        totalOriginals += m_levels.at(i)->originalEmployees();
    }
    setOriginals(totalOriginals);
}

void ModifiedMartellIdea::resetDisplay()
{
    if(valid())
    {
        emit setupPieChart(m_paramsEtc->getNumGroups(), m_paramsEtc->getPieChartSweeps(), m_paramsEtc->getGroupColors());
        emit setupNameRectangles(m_paramsEtc->getNumGroups(), m_paramsEtc->getGroupNames(), m_paramsEtc->getGroupColors());
        emit percentWomenChanged(m_percentWomen);
        emit meanScoreChanged(m_meanScore);
        emit originalsChanged(m_originals);
        emit promotionCyclesChanged(m_promotionCycles);
    }
}
