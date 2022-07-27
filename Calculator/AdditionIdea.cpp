#include "AdditionIdea.h"

AdditionAttributes::AdditionAttributes()
{
    m_listName = "Addition";
    m_displayName = "Addition";
    m_authors << "dBob";
    m_description = "Addition of two decimal-type numbers";
    m_iconPath = "qrc:/Icons/Addition.png";

    m_dataTypesIn << Magic<NumberDataTypeAttributes>::cast().id() << Magic<NumberDataTypeAttributes>::cast().id();
    m_dataTypesOut << Magic<NumberDataTypeAttributes>::cast().id();

    m_gear = true;

    m_embeddedQMLPath = ":/QML/AdditionIdea.qml";
}

AdditionIdea::AdditionIdea()
{
    m_inPortLabelColors.append("#d4985d");
    m_inPortLabelColors.append("#b14343");
    m_outPortLabelColors.append("#a942ea");
}

const IdeaAttributes AdditionIdea::attributes()
{
    return Magic<AdditionAttributes>::cast();
}


void AdditionIdea::validate()
{
    auto n1 = m_input1.lock();
    auto n2 = m_input2.lock();

    if(n1 && n2)
    {
        setStatus(IdeaStatus::Working, "Adding", "Adding " + QString::number(n1->number()) + " + " + QString::number(n2->number()));
        compute(n1->number(),n2->number());
        emit display(n1->number(), n2->number(), n1->number() + n2->number());
    }
    else
    {
        setDefaultStatus();
        emit clear();
    }
}

void AdditionIdea::compute(double n1, double n2)
{
    emit startSpinningGear();
    m_result = std::make_shared<NumberDataType>(n1+n2);
    emit newData(0);
    emit stopSpinningGear();
}


