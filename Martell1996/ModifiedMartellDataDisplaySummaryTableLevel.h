#ifndef MARTELL1996TABLELEVEL_H
#define MARTELL1996TABLELEVEL_H

#include <QObject>

class ModifiedMartellDataDisplaySummaryTableLevel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(double meanScore READ meanScore WRITE setMeanScore NOTIFY meanScoreChanged)
    Q_PROPERTY(double meanScoreErr READ meanScoreErr WRITE setMeanScoreErr NOTIFY meanScoreErrChanged)
    Q_PROPERTY(int numPositions READ numPositions WRITE setNumPositions NOTIFY numPositionsChanged)
    Q_PROPERTY(double percentWomen READ percentWomen WRITE setPercentWomen NOTIFY percentWomenChanged)
    Q_PROPERTY(double percentWomenErr READ percentWomenErr WRITE setPercentWomenErr NOTIFY percentWomenErrChanged)

public:
    explicit ModifiedMartellDataDisplaySummaryTableLevel(QObject *parent = nullptr);
    ModifiedMartellDataDisplaySummaryTableLevel(const int level, const double meanScore, const double meanScoreErr,
                          const int numPositions, const double percentWomen,
                          const double percentWomenErr, QObject* parent);

    int level() const;
    double meanScore() const;
    double meanScoreErr() const;
    int numPositions() const;
    double percentWomen() const;
    double percentWomenErr() const;

public slots:
    void setLevel(int level);
    void setMeanScore(double meanScore);
    void setMeanScoreErr(double meanScoreErr);
    void setNumPositions(int numPositions);
    void setPercentWomen(double percentWomen);
    void setPercentWomenErr(double percentWomenErr);

signals:
    void levelChanged(int level);
    void meanScoreChanged(double meanScore);
    void meanScoreErrChanged(double meanScoreErr);
    void percentWomenChanged(double percentWomen);
    void numPositionsChanged(int numPositions);
    void percentWomenErrChanged(double percentWomenErr);

private:
    int m_level;
    double m_meanScore;
    double m_meanScoreErr;
    int m_numPositions;
    double m_percentWomen;
    double m_percentWomenErr;
};

#endif // MARTELL1996TABLELEVEL_H
