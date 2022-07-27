#include "ModifiedMartellDataDisplaySummaryTableModel.h"

ModifiedMartellDataDisplaySummaryTableModel::ModifiedMartellDataDisplaySummaryTableModel(QObject *parent) : QAbstractListModel(parent)
{

}


int ModifiedMartellDataDisplaySummaryTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_levels.size();
}

QVariant ModifiedMartellDataDisplaySummaryTableModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_levels.size())
        return QVariant();

    ModifiedMartellDataDisplaySummaryTableLevel* level = m_levels.at(index.row());
    if(role == LevelRole)
        return QVariant(level->level());
    if(role == MeanScoreRole)
        return QVariant(level->meanScore());
    if(role == NumPositionsRole)
        return QVariant(level->numPositions());
    if(role == PercentWomenRole)
        return QVariant(level->percentWomen());
    if(role == MeanScoreErrRole)
        return QVariant(level->meanScoreErr());
    if(role == PercentWomenErrRole)
        return QVariant(level->percentWomenErr());

    return QVariant();

}

bool ModifiedMartellDataDisplaySummaryTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    ModifiedMartellDataDisplaySummaryTableLevel* level = m_levels.at(index.row());
    bool somethingChanged = false;

    switch (role)
    {
    case LevelRole:
    {
        if(level->level() != value.toInt())
        {
            level->setLevel(value.toInt());
            somethingChanged = true;
        }
        break;
    }
    case MeanScoreRole:
    {
        if(level->meanScore() != value.toDouble())
        {
            level->setMeanScore(value.toDouble());
            somethingChanged = true;
        }
        break;
    }
    case NumPositionsRole:
    {
        if(level->numPositions() != value.toInt())
        {
            level->setNumPositions(value.toInt());
            somethingChanged = true;
        }
        break;
    }
    case PercentWomenRole:
    {
        if(level->percentWomen() != value.toDouble())
        {
            level->setPercentWomen(value.toDouble());
            somethingChanged = true;
        }
        break;
    }
    case MeanScoreErrRole:
    {
        if(level->meanScoreErr() != value.toDouble())
        {
            level->setMeanScoreErr(value.toDouble());
            somethingChanged = true;
        }

    }
    case PercentWomenErrRole:
    {
        if(level->percentWomenErr() != value.toDouble())
        {
            level->setPercentWomenErr(value.toDouble());
            somethingChanged = true;
        }
    }
    }

    if(somethingChanged)
    {
        emit dataChanged(index,index,QVector<int>() << role);
        return true;
    }

    return false;
}
Qt::ItemFlags ModifiedMartellDataDisplaySummaryTableModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ModifiedMartellDataDisplaySummaryTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[LevelRole] = "level";
    roles[MeanScoreRole] = "meanScore";
    roles[NumPositionsRole] = "positions";
    roles[PercentWomenRole] = "percentWomen";
    roles[MeanScoreErrRole] = "meanScoreError";
    roles[PercentWomenErrRole] = "percentWomenError";
    return roles;
}

void ModifiedMartellDataDisplaySummaryTableModel::addLevel(int level, double meanScore, double meanScoreErr, int numPositions, double percentWomen, double percentWomenErr)
{
    ModifiedMartellDataDisplaySummaryTableLevel* tableLevel = new ModifiedMartellDataDisplaySummaryTableLevel(level,meanScore, meanScoreErr, numPositions,
                                                                  percentWomen, percentWomenErr, this);

    const int index = m_levels.size();
    beginInsertRows(QModelIndex(), index,index);
    m_levels.append(tableLevel);
    endInsertRows();
}

void ModifiedMartellDataDisplaySummaryTableModel::clearData()
{
    beginRemoveRows(QModelIndex(),0, 7);
    m_levels.clear();
    endRemoveRows();
}
