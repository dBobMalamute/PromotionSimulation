#include "ModifiedMartellDataDisplaySummaryTableLevel.h"

ModifiedMartellDataDisplaySummaryTableLevel::ModifiedMartellDataDisplaySummaryTableLevel(QObject *parent) : QObject(parent)
{

}

ModifiedMartellDataDisplaySummaryTableLevel::ModifiedMartellDataDisplaySummaryTableLevel(const int level, const double meanScore, const double meanScoreErr,
                                             const int numPositions, const double percentWomen,
                                             const double percentWomenErr, QObject* parent) :
    QObject(parent),
    m_level(level),
    m_meanScore(meanScore),
    m_meanScoreErr(meanScoreErr),
    m_numPositions(numPositions),
    m_percentWomen(percentWomen),
    m_percentWomenErr(percentWomenErr)
{

}

int ModifiedMartellDataDisplaySummaryTableLevel::level() const
{
    return m_level;
}

double ModifiedMartellDataDisplaySummaryTableLevel::meanScore() const
{
    return m_meanScore;
}

double ModifiedMartellDataDisplaySummaryTableLevel::percentWomen() const
{
    return m_percentWomen;
}

double ModifiedMartellDataDisplaySummaryTableLevel::percentWomenErr() const
{
    return m_percentWomenErr;
}

double ModifiedMartellDataDisplaySummaryTableLevel::meanScoreErr() const
{
    return m_meanScoreErr;
}

void ModifiedMartellDataDisplaySummaryTableLevel::setLevel(int level)
{
    if (m_level == level)
        return;

    m_level = level;
    emit levelChanged(m_level);
}

void ModifiedMartellDataDisplaySummaryTableLevel::setMeanScore(double meanScore)
{
    if (qFuzzyCompare(m_meanScore, meanScore))
        return;

    m_meanScore = meanScore;
    emit meanScoreChanged(m_meanScore);
}

void ModifiedMartellDataDisplaySummaryTableLevel::setPercentWomen(double percentWomen)
{
    if (qFuzzyCompare(m_percentWomen, percentWomen))
        return;

    m_percentWomen = percentWomen;
    emit percentWomenChanged(m_percentWomen);
}

void ModifiedMartellDataDisplaySummaryTableLevel::setMeanScoreErr(double meanScoreErr)
{
    if (qFuzzyCompare(m_meanScoreErr, meanScoreErr))
        return;

    m_meanScoreErr = meanScoreErr;
    emit meanScoreErrChanged(m_meanScoreErr);
}

void ModifiedMartellDataDisplaySummaryTableLevel::setPercentWomenErr(double percentWomenErr)
{
    if (qFuzzyCompare(m_percentWomenErr, percentWomenErr))
        return;

    m_percentWomenErr = percentWomenErr;
    emit percentWomenErrChanged(m_percentWomenErr);
}

void ModifiedMartellDataDisplaySummaryTableLevel::setNumPositions(int numPositions)
{
    if (m_numPositions == numPositions)
        return;

    m_numPositions = numPositions;
    emit numPositionsChanged(m_numPositions);
}

int ModifiedMartellDataDisplaySummaryTableLevel::numPositions() const
{
    return m_numPositions;
}
