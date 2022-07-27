#include "Idea.h"

#include <QClipboard>
#include <QMimeData>
#include <QApplication>

Idea::~Idea()
{

}

QJsonObject Idea::save() const
{
    QJsonObject saveJson;
    QJsonArray arr;
    for(int i = 0; i < m_inPortLabelColors.size(); i++)
        arr.append(m_inPortLabelColors.at(i).name());
    saveJson["ci"] = arr;
    QJsonArray arr2;
    for(int i = 0; i < m_outPortLabelColors.size(); i++)
        arr2.append(m_outPortLabelColors.at(i).name());
    saveJson["co"] = arr2;
    return saveJson;
}

void Idea::load(const QJsonObject &obj)
{
    QJsonValue v = obj["ci"];
    if(!v.isUndefined())
    {
        m_inPortLabelColors.clear();
        QJsonArray arr = v.toArray();
        for(int i = 0; i < arr.size(); i++)
            m_inPortLabelColors.append(QColor(arr.at(i).toString()));
        emit inPortLabelColorsChanged(m_inPortLabelColors);
    }
    v = obj["co"];
    if(!v.isUndefined())
    {
        m_outPortLabelColors.clear();
        QJsonArray arr = v.toArray();
        for(int i = 0; i < arr.size(); i++)
            m_outPortLabelColors.append(QColor(arr.at(i).toString()));
        emit outPortLabelColorsChanged(m_outPortLabelColors);
    }
}

void Idea::onNewDataIn(std::shared_ptr<DataType>, PlugNumber)
{

}

std::shared_ptr<DataType> Idea::dataOut(PlugNumber)
{
    return nullptr;
}

void Idea::resetDisplay()
{

}

void Idea::finishSetupQmlContext()
{

}

QString Idea::shortStatusMessage() const
{
    return m_shortStatusMessage;
}

QString Idea::longStatusMessage() const
{
    return m_longStatusMessage;
}

IdeaStatus Idea::status() const
{
    return m_status;
}

bool Idea::valid() const
{
    if(m_status == IdeaStatus::Working || m_status == IdeaStatus::Warning || m_status == IdeaStatus::DisplayWarning)
        return true;
    else
        return false;
}

bool Idea::minimized() const
{
    return m_minimized;
}

QList<QColor> Idea::inPortLabelColors() const
{
    return m_inPortLabelColors;
}

QList<QColor> Idea::outPortLabelColors() const
{
    return m_outPortLabelColors;
}


void Idea::setStatus(IdeaStatus status, QString shortMessage, QString longMessage)
{
    m_status = status;
    m_shortStatusMessage = shortMessage;
    m_longStatusMessage = longMessage;
    emit statusChanged();

    if(status == IdeaStatus::StandBy || status == IdeaStatus::Error || status == IdeaStatus::Fatal)
    {
        emit clearDataAllPlugs();
        emit validChanged(false);
    }
    else
    {
        emit validChanged(true);
    }
}

void Idea::setDefaultStatus()
{
    IdeaStatus oldStatus = m_status;
    m_status = IdeaStatus::StandBy;
    m_shortStatusMessage = "Standing By";
    m_longStatusMessage = "Waiting for user input";
    emit statusChanged();
    emit validChanged(false);

    //Clear data if necessary
    if(oldStatus == IdeaStatus::Working || oldStatus == IdeaStatus::Warning || oldStatus == IdeaStatus::DisplayWarning)
        emit clearDataAllPlugs();
}

void Idea::sendTextToClipboard(QString text)
{
    QMimeData* mimeData = new QMimeData;
    mimeData->setText(text);

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);
}

void Idea::setMinimized(bool minimized)
{
    if (m_minimized == minimized)
        return;

    m_minimized = minimized;
    emit minimizedChanged(m_minimized);
}

void Idea::setInPortLabelColor(int i, QColor color)
{
    if(m_inPortLabelColors.at(i) == color)
        return;

    m_inPortLabelColors[i] = color;
    emit inPortLabelColorsChanged(m_inPortLabelColors);
}

void Idea::setOutPortLabelColor(int i, QColor color)
{
    if(m_outPortLabelColors.at(i) == color)
        return;

    m_outPortLabelColors[i] = color;
    emit outPortLabelColorsChanged(m_outPortLabelColors);
}
