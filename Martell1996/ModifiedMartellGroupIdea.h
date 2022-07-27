#ifndef MODIFIEDMARTELLGROUPIDEA_H
#define MODIFIEDMARTELLGROUPIDEA_H

#include <QObject>
#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "../DataTypes/DistributionDataType.h"
#include "ModifiedMartellParamsEtc.h"
#include "ModifiedMartellGroupDataType.h"
#include "SimulationGender.h"

struct ModifiedMartellGroupAttributes : public IdeaAttributes
{
    ModifiedMartellGroupAttributes();
};

class ModifiedMartellGroupIdea : public Idea
{
    Q_OBJECT

    Q_PROPERTY(QString groupName READ groupName WRITE setGroupName NOTIFY groupNameChanged)
    Q_PROPERTY(int groupColor READ groupColor WRITE setGroupColor NOTIFY groupColorChanged)
    Q_PROPERTY(SimulationGender::GENDER groupGender READ groupGender WRITE setGroupGender NOTIFY groupGenderChanged)
    Q_PROPERTY(double groupPercent READ groupPercent WRITE setGroupPercent NOTIFY groupPercentChanged)

public:
    ModifiedMartellGroupIdea();
    const IdeaAttributes attributes() override;

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    QString groupName() const;
    int groupColor() const;
    SimulationGender::GENDER groupGender() const;
    double groupPercent() const;

public slots:
    void setGroupName(QString groupName);
    void setGroupColor(int groupColor);
    void setGroupGender(SimulationGender::GENDER groupGender);
    void setGroupGenderInt(int groupGender);
    int getGroupGenderInt();
    void setGroupPercent(double groupPercent);

    QColor getColor();

signals:
    void groupNameChanged(QString groupName);
    void groupColorChanged(int groupColor);
    void groupGenderChanged(SimulationGender::GENDER groupGender);
    void groupPercentChanged(double groupPercent);

private:
    std::weak_ptr<DistributionDataType> m_skillInput;

    std::shared_ptr<ModifiedMartellGroupDataType> m_result;

    void validate();
    void compute();

    QString m_groupName;
    int m_groupColor;
    SimulationGender::GENDER m_groupGender;
    double m_groupPercent;
};

#endif // MODIFIEDMARTELLGROUPIDEA_H
