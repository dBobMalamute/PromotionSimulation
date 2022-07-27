#ifndef MODIFIEDMARTELLORGANIZATIONLEVEL_H
#define MODIFIEDMARTELLORGANIZATIONLEVEL_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QRectF>

#include "ModifiedMartellPerson.h"
#include "ModifiedMartellParamsEtc.h"
#include <QRandomGenerator>

class PoissonSampler : public DistributionSampler
{
public:
    PoissonSampler(double mean):
        m_mean(mean)
    {
        m_L = qExp(-1.0 * m_mean);
    }
    QList<double> getSamples(int n)
    {
        QList<double> samples;
        samples.reserve(n);
        for(int i = 0; i < n; i++)
        {
            double p = 1.0;
            int k = 0;
            while(p > m_L)
            {
                k += 1;
                p *= QRandomGenerator::global()->generateDouble();
            }

            samples.append(k - 1);
        }
        return samples;
    }

private:
    double m_mean;
    double m_L;
};

class ModifiedMartellOrganizationLevel : public QObject
{
    Q_OBJECT

    enum PersonRoles
    {
        ColorRole = Qt::UserRole + 1,
        ScoreRole,
        OriginalRole
    };

public:
    explicit ModifiedMartellOrganizationLevel(ModifiedMartellParamsEtc* params, int level, QObject *parent = nullptr);
    ~ModifiedMartellOrganizationLevel();

    int positions() const;

    void reset(bool animate = false, bool updateDisplay = true);
    void attrition(bool animate);
    int numberEmptyPositions();
    std::vector<std::unique_ptr<ModifiedMartellPerson>> promote(int n);
    void addPromoted(std::vector<std::unique_ptr<ModifiedMartellPerson>> newPersons, bool animate = false, bool updateDisplay = false);
    void addNewHires(bool animate, bool updateDisplay = true);

    void updateDisplay();

    double percentWomen();
    double averageScore();
    int originalEmployees();

    void setPositiveAttrition(double positiveAttrition);
    void setRandomAttrition(double randomAttrition);
    void setNegativeAttrition(double negativeAttrition);
    void setPositions(int positions);

private:
    ModifiedMartellParamsEtc* m_paramsEtc;

    int m_level;
    int m_numberPositions;
    double m_positiveAttrition;
    double m_randomAttrition;
    double m_negativeAttrition;

    std::vector<std::unique_ptr<ModifiedMartellPerson>> m_persons;
    std::vector<int> m_emptySlots;

    int sampleBinomial(double num, double prob);
};

#endif // MODIFIEDMARTELLORGANIZATIONLEVEL_H
