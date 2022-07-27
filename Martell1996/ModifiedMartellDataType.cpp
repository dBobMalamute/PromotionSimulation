#include "ModifiedMartellDataType.h"

QList<double> runData::percentWomen() const
{
    return m_percentWomen;
}

QList<double> runData::averageScore() const
{
    return m_averageScore;
}

int runData::promotionCycles() const
{
    return m_promotionCycles;
}

ModifiedMartellDataTypeAttributes::ModifiedMartellDataTypeAttributes()
{
    m_name = "Modified Martell simulation data output";
    m_color = "#6a6acc";
    m_abbreviation = "data";
    m_description = "Holds the data for export for Modified Martell.";
    m_authors << "dBob";
}

DataTypeAttributes ModifiedMartellDataType::getAttributes()
{
    return Magic<ModifiedMartellDataTypeAttributes>::cast();
}

QList<runData> ModifiedMartellDataType::getRunData() const
{
    return m_runData;
}

int ModifiedMartellDataType::getNumRuns() const
{
    return m_numRuns;
}

QList<int> ModifiedMartellDataType::getPositionsAtLevel() const
{
    return m_positionsAtLevel;
}

ModifiedMartellDataType::ModifiedMartellDataType()
{
    m_numRuns = 0;
    m_runData = QList<runData>();
}

ModifiedMartellDataType::ModifiedMartellDataType(int numRuns, QList<int> positionsAtLevel,
                                                 QList<runData> m_runData) :
    m_numRuns(numRuns),
    m_positionsAtLevel(positionsAtLevel),
    m_runData(m_runData)
{

}

