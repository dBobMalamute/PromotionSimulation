#include "ModifiedMartellGroupIdea.h"

ModifiedMartellGroupAttributes::ModifiedMartellGroupAttributes()
{
    m_listName = "Modified Martell Group";
    m_displayName = "";
    m_authors << "dBob";
    m_description = "A group for the modified martell simulation";
    m_iconPath =  "qrc:/Icons/ModifiedMartellGroup.png";

    m_dataTypesIn << Magic<DistributionDataTypeAttributes>::cast().id();
    m_dataTypesOut << Magic<ModifiedMartellGroupDataTypeAttributes>::cast().id();

    m_labelsIn << "";
    m_labelsOut << "";
    m_customLabels = true;

    m_embeddedQMLPath = ":/QML/ModifiedMartellGroup.qml";
    m_minimizedQMLPath = ":/QML/ModifiedMartellGroupMinimized.qml";
    m_minimizable = true;
    m_startMinimized = false;
}

ModifiedMartellGroupIdea::ModifiedMartellGroupIdea() :
    m_groupName("Name"),
    m_groupColor(0),
    m_groupGender(SimulationGender::UNSPECIFIED),
    m_groupPercent(0.0)
{

}

const IdeaAttributes ModifiedMartellGroupIdea::attributes()
{
    return Magic<ModifiedMartellGroupAttributes>::cast();
}

QJsonObject ModifiedMartellGroupIdea::save() const
{
    QJsonObject saveJson = Idea::save();
    saveJson["n"] = m_groupName;
    saveJson["c"] = m_groupColor;
    saveJson["g"] = m_groupGender;
    saveJson["p"] = m_groupPercent;

    return saveJson;
}

void ModifiedMartellGroupIdea::load(const QJsonObject &obj)
{
    QJsonValue v = obj["n"];
    if(!v.isUndefined())
    {
        m_groupName = v.toString();
        emit groupNameChanged(m_groupName);
    }

    v = obj["c"];
    if(!v.isUndefined())
    {
        m_groupColor = v.toInt();
        emit groupColorChanged(m_groupColor);
    }

    v = obj["g"];
    if(!v.isUndefined())
    {
        m_groupGender = static_cast<SimulationGender::GENDER>(v.toInt());
        emit groupGenderChanged(m_groupGender);
    }

    v = obj["p"];
    if(!v.isUndefined())
    {
        m_groupPercent = v.toDouble();
        emit groupPercentChanged(m_groupPercent);
    }

    validate();
}

void ModifiedMartellGroupIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto input = std::dynamic_pointer_cast<DistributionDataType>(dataType);
    m_skillInput = input;

    validate();
}

std::shared_ptr<DataType> ModifiedMartellGroupIdea::dataOut(PlugNumber)
{
    return std::static_pointer_cast<DataType>(m_result);
}

QString ModifiedMartellGroupIdea::groupName() const
{
    return m_groupName;
}

int ModifiedMartellGroupIdea::groupColor() const
{
    return m_groupColor;
}

SimulationGender::GENDER ModifiedMartellGroupIdea::groupGender() const
{
    return m_groupGender;
}

double ModifiedMartellGroupIdea::groupPercent() const
{
    return m_groupPercent;
}

void ModifiedMartellGroupIdea::setGroupName(QString groupName)
{
    if (m_groupName == groupName)
        return;

    QJsonObject oldParams;
    oldParams["n"] = m_groupName;

    m_groupName = groupName;
    emit groupNameChanged(m_groupName);

    QJsonObject newParams;
    newParams["n"] = m_groupName;
    reportParamsChanged(oldParams, newParams);

    validate();
}

void ModifiedMartellGroupIdea::setGroupColor(int groupColor)
{
    if (m_groupColor == groupColor)
        return;

    QJsonObject oldParams;
    oldParams["c"] = m_groupColor;

    m_groupColor = groupColor;
    emit groupColorChanged(m_groupColor);

    QJsonObject newParams;
    newParams["c"] = m_groupColor;
    reportParamsChanged(oldParams, newParams);

    validate();
}

void ModifiedMartellGroupIdea::setGroupGender(SimulationGender::GENDER groupGender)
{
    if (m_groupGender == groupGender)
        return;

    QJsonObject oldParams;
    oldParams["g"] = m_groupGender;

    m_groupGender = groupGender;
    emit groupGenderChanged(m_groupGender);

    QJsonObject newParams;
    newParams["g"] = m_groupGender;
    reportParamsChanged(oldParams, newParams);

    validate();
}

void ModifiedMartellGroupIdea::setGroupGenderInt(int groupGender)
{
    if (m_groupGender == groupGender)
        return;

    QJsonObject oldParams;
    oldParams["g"] = m_groupGender;

    m_groupGender = static_cast<SimulationGender::GENDER>(groupGender);
    emit groupGenderChanged(m_groupGender);

    QJsonObject newParams;
    newParams["g"] = m_groupGender;
    reportParamsChanged(oldParams, newParams);

    validate();
}

int ModifiedMartellGroupIdea::getGroupGenderInt()
{
    return static_cast<int>(m_groupGender);
}

void ModifiedMartellGroupIdea::setGroupPercent(double groupPercent)
{
    if (qFuzzyCompare(m_groupPercent, groupPercent))
        return;

    QJsonObject oldParams;
    oldParams["p"] = m_groupPercent;

    m_groupPercent = groupPercent;
    emit groupPercentChanged(m_groupPercent);

    QJsonObject newParams;
    newParams["p"] = m_groupPercent;
    reportParamsChanged(oldParams, newParams);

    validate();
}

QColor ModifiedMartellGroupIdea::getColor()
{
    return ModifiedMartellParamsEtc::getColorFromIndex(m_groupColor);
}

void ModifiedMartellGroupIdea::validate()
{
    auto n = m_skillInput.lock();

    if(n) //Is there an input distribution.
    {
        if(groupName() == "")
        {
            setStatus(IdeaStatus::Error, "No Name", "Please set a group name");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Setting up Group", "Setting up a group");
            compute();
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void ModifiedMartellGroupIdea::compute()
{
    auto n1 = m_skillInput.lock();
    m_result = std::make_shared<ModifiedMartellGroupDataType>(groupName(), groupColor(), groupGender(), groupPercent(),
                                                              n1);

    emit newData(0);
}
