#ifndef MODIFIEDMARTELLPARAMSETC_H
#define MODIFIEDMARTELLPARAMSETC_H

#include <QRandomGenerator>
#include <QList>
#include <QColor>
#include "ModifiedMartellGroupDataType.h"
#include "ModifiedMartellPerson.h"
#include "../Distributions/Common/DistributionCommonFunctions.h"
#include "ModifiedMartellPersonDotsGoverner.h"

#include <memory>

class ModifiedMartellGroupDataType;

class ModifiedMartellParamsEtc
{
public:
    ModifiedMartellParamsEtc();

    static QColor getColorFromIndex(int index);
    static int getIndexFromColor(QColor color);

    void resetGroups();
    void addGroup(std::shared_ptr<ModifiedMartellGroupDataType> group);
    bool setupCumulativePercentages();
    void setupScoreCDFs();

    int getNumGroups() const;
    QList<double> getPieChartSweeps();
    QList<QColor> getGroupColors() const;
    QList<QString> getGroupNames() const;
    SimulationGender::GENDER getGender(int i);

    std::unique_ptr<ModifiedMartellPerson> generatePerson(int level, int positionInLevel, bool original = false);

    bool calculateCohensD(double &d);

    void setGoverner(ModifiedMartellPersonDotsGoverner *governer);

private:
    int m_numGroups;
    QList<double> m_groupPercentages;
    QList<double> m_cumulativeGroupPercentages;
    QList<QString> m_groupNames;
    QList<QColor> m_groupColors;
    QList<SimulationGender::GENDER> m_groupGenders;

    QList<std::shared_ptr<DistributionSampler>> m_samplers;
    QList<double> m_groupMeans;
    QList<double> m_groupVariances;

    ModifiedMartellPersonDotsGoverner* m_governer;

    double sampleScoreCDF(int i);
};

#endif // MODIFIEDMARTELLPARAMSETC_H
