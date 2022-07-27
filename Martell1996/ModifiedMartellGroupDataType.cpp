#include "ModifiedMartellGroupDataType.h"

ModifiedMartellGroupDataTypeAttributes::ModifiedMartellGroupDataTypeAttributes()
{
    m_name = "Modified Martell Group Data";
    m_color = "#095bb5";
    m_abbreviation = "data";
    m_description = "This data type holds the group data for the modified simulation";
    m_authors << "dBob";

    m_defaultSource = "Modified Martell Group";
    m_defaultDisplay = "Modified Martell Simulation";
}

ModifiedMartellGroupDataType::ModifiedMartellGroupDataType(QString groupName, int groupColor,
                                                           SimulationGender::GENDER groupGender, double groupPercentage,
                                                           std::shared_ptr<DistributionDataType> distribution):
    m_groupName(groupName),
    m_groupColor(groupColor),
    m_groupGender(groupGender),
    m_groupPercentage(groupPercentage),
    m_distribution(distribution)
{

}

QString ModifiedMartellGroupDataType::groupName() const
{
    return m_groupName;
}

int ModifiedMartellGroupDataType::groupColor() const
{
    return m_groupColor;
}

SimulationGender::GENDER ModifiedMartellGroupDataType::groupGender() const
{
    return m_groupGender;
}

double ModifiedMartellGroupDataType::groupPercentage() const
{
    return m_groupPercentage;
}

std::shared_ptr<DistributionDataType> ModifiedMartellGroupDataType::getDistribution() const
{
    return m_distribution;
}

DataTypeAttributes ModifiedMartellGroupDataType::getAttributes()
{
    return Magic<ModifiedMartellGroupDataTypeAttributes>::cast();
}
