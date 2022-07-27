#ifndef MODIFIEDMARTELLGROUPDATATYPE_H
#define MODIFIEDMARTELLGROUPDATATYPE_H

#include "../MalamuteCore/InheritedClasses/DataType.h"
#include "../DataTypes/DistributionDataType.h"
#include "SimulationGender.h"

struct ModifiedMartellGroupDataTypeAttributes : public DataTypeAttributes
{
    ModifiedMartellGroupDataTypeAttributes();
};

class ModifiedMartellGroupDataType : public DataType
{
public:
    ModifiedMartellGroupDataType(QString groupName, int groupColor, SimulationGender::GENDER groupGender,
                                 double groupPercentage, std::shared_ptr<DistributionDataType> distribution);

    DataTypeAttributes getAttributes() override;

    QString groupName() const;
    int groupColor() const;
    SimulationGender::GENDER groupGender() const;
    double groupPercentage() const;

    std::shared_ptr<DistributionDataType> getDistribution() const;

private:
    QString m_groupName;
    int m_groupColor;
    SimulationGender::GENDER m_groupGender;
    double m_groupPercentage;

    std::shared_ptr<DistributionDataType> m_distribution;
};

#endif // MODIFIEDMARTELLGROUPDATATYPE_H
