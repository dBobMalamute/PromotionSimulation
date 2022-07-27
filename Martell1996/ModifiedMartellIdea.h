#ifndef MARTELL4GROUPSIDEA_H
#define MARTELL4GROUPSIDEA_H

#include <QPointF>
#include <QTimer>
#include <QQuickItem>

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "../DataTypes/DistributionDataType.h"
#include "ModifiedMartellDataType.h"

#include "ModifiedMartellOrganizationLevel.h"

#include "ModifiedMartellParamsEtc.h"
#include "ModifiedMartellPersonDotsGoverner.h"
#include "ModifiedMartellGroupDataType.h"
#include "SimulationMode.h"

struct ModifiedMartellAttributes : public IdeaAttributes
{
    ModifiedMartellAttributes();
};

class ModifiedMartellIdea : public Idea
{
    Q_OBJECT

    Q_PROPERTY(int numLevels READ numLevels WRITE setNumLevels NOTIFY numLevelsChanged)
    Q_PROPERTY(QList<int> positionsAtLevel READ positionsAtLevel WRITE setPositionsAtLevel NOTIFY positionsAtLevelChanged)

    Q_PROPERTY(QList<double> positiveAttrition READ positiveAttrition NOTIFY positiveAttritionChanged)
    Q_PROPERTY(QList<double> randomAttrition READ randomAttrition NOTIFY randomAttritionChanged)
    Q_PROPERTY(QList<double> negativeAttrition READ negativeAttrition NOTIFY negativeAttritionChanged)

    Q_PROPERTY(QList<QVariant> percentWomen READ percentWomen WRITE setPercentWomen NOTIFY percentWomenChanged)
    Q_PROPERTY(QList<QVariant> meanScore READ meanScore WRITE setMeanScore NOTIFY meanScoreChanged)

    Q_PROPERTY(int originals READ originals WRITE setOriginals NOTIFY originalsChanged)
    Q_PROPERTY(int promotionCycles READ promotionCycles WRITE setPromotionCycles NOTIFY promotionCyclesChanged)

    Q_PROPERTY(SimulationMode::SimulationModeEnum mode READ mode WRITE setMode NOTIFY modeChanged)

    Q_PROPERTY(int bulkRunNum READ bulkRunNum WRITE setBulkRunNum NOTIFY bulkRunNumChanged)

    Q_PROPERTY(bool stopAtNoOriginals READ stopAtNoOriginals WRITE setStopAtNoOriginals NOTIFY stopAtNoOriginalsChanged)
    Q_PROPERTY(int cyclesToStopAt READ cyclesToStopAt WRITE setCyclesToStopAt NOTIFY cyclesToStopAtChanged)

    enum NextAction
    {
        AttritionStart,
        PromoteFromWithinStart,
        NewHiresStart
    };

public:
    explicit ModifiedMartellIdea();
    ~ModifiedMartellIdea();
    const IdeaAttributes attributes() override;

    void finishSetupQmlContext() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    void resetDisplay() override;

    QList<QVariant> percentWomen() const;
    QList<QVariant> meanScore() const;

    int originals() const;
    int promotionCycles() const;

    int bulkRunNum() const;

    SimulationMode::SimulationModeEnum mode() const;

    int numLevels() const;
    QList<int> positionsAtLevel() const;

    QList<double> positiveAttrition() const;
    QList<double> randomAttrition() const;
    QList<double> negativeAttrition() const;

    bool stopAtNoOriginals() const;
    int cyclesToStopAt() const;

private:
    std::weak_ptr<ModifiedMartellGroupDataType> m_group1;
    std::weak_ptr<ModifiedMartellGroupDataType> m_group2;
    std::weak_ptr<ModifiedMartellGroupDataType> m_group3;
    std::weak_ptr<ModifiedMartellGroupDataType> m_group4;
    std::weak_ptr<ModifiedMartellGroupDataType> m_group5;
    std::weak_ptr<ModifiedMartellGroupDataType> m_group6;

    std::shared_ptr<ModifiedMartellDataType> m_dataOut;

    void validate();
    void calculateCohensD();

signals:
    void percentWomenChanged(QList<QVariant> percentWomen);
    void meanScoreChanged(QList<QVariant> meanScore);
    void originalsChanged(int originals);
    void promotionCyclesChanged(int promotionCycles);
    void modeChanged(SimulationMode::SimulationModeEnum mode);

    void bulkRunNumChanged(int bulkRunNum);

    void setupPieChart(int numSections, QList<double> sweeps, QList<QColor> colors);
    void setupNameRectangles(int numRects, QList<QString> names, QList<QColor> colors);
    void showCohensD(double d);
    void hideCohensD();

    void numLevelsChanged(int numLevels);
    void positionsAtLevelChanged(QList<int> positionsAtLevel);

    void positiveAttritionChanged(QList<double> positiveAttrition);
    void randomAttritionChanged(QList<double> randomAttrition);
    void negativeAttritionChanged(QList<double> negativeAttrition);

    void stopAtNoOriginalsChanged(bool stopAtNoOriginals);
    void cyclesToStopAtChanged(int cyclesToStopAt);

public slots:
    void normalStepButtonClicked();
    void normalFinishButtonClicked();
    void normalResetButtonClicked();

    void animationStepButtonClicked();
    void animationResetButtonClicked();

    void bulkRun();

    void attritionStep();
    void promoteFromWithin();
    void fillLowestLevelNewHires();

    void bulkRunButtonClicked();

    void nextActionFromTimer();

    void setPercentWomen(QList<QVariant> percentWomen);
    void setMeanScore(QList<QVariant> meanScore);
    void setOriginals(int originals);
    void setPromotionCycles(int promotionCycles);

    void setMode(SimulationMode::SimulationModeEnum mode);

    void setBulkRunNum(int bulkRunNum);

    void setNumLevels(int numLevels);
    void setPositionAtOneLevel(int level, int positions);
    void setPositionsAtLevel(QList<int> positionsAtLevel);

    void setPositiveAttrition(int level, double attritionRate);
    void setRandomAttrition(int level, double attritionRate);
    void setNegativeAttrition(int level, double attritionRate);

    void setupPersonDotsArea(QQuickItem* item);

    void setStopAtNoOriginals(bool stopAtNoOriginals);
    void setCyclesToStopAt(int cyclesToStopAt);

private:
    ModifiedMartellParamsEtc* m_paramsEtc;
    ModifiedMartellPersonDotsGoverner m_dotsGoverner;

    void normalStep(bool updateDisplay = true);
    void setup();
    void reset(bool animate = false, bool updateDisplay = true);
    void updateStatistics();

    QList<QVariant> m_percentWomen;
    QList<QVariant> m_meanScore;

    int m_originals;
    int m_promotionCycles;

    NextAction nextAction = AttritionStart;

    int m_bulkRunNum;
    QList<runData> m_bulkRunData;
    SimulationMode::SimulationModeEnum m_mode;

    int m_numLevels;
    QList<int> m_positionsAtLevel; //Top to bottom; 0 to numLevels -1

    QList<ModifiedMartellOrganizationLevel*> m_levels;
    QList<double> m_positiveAttrition;
    QList<double> m_randomAttrition;
    QList<double> m_negativeAttrition;
    bool m_modeChanged;
    bool m_stopAtNoOriginals;
    int m_cyclesToStopAt;
};

#endif // MARTELL4GROUPSIDEA_H
