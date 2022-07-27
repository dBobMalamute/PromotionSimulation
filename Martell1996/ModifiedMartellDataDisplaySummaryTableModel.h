#ifndef MARTELL1996SUMMARYTABLEMODEL_H
#define MARTELL1996SUMMARYTABLEMODEL_H

#include <QObject>
#include <QDebug>
#include <QAbstractListModel>
#include "ModifiedMartellDataDisplaySummaryTableLevel.h"

class ModifiedMartellDataDisplaySummaryTableModel : public QAbstractListModel
{
    Q_OBJECT

    enum TableLevelRoles
    {
        LevelRole = Qt::UserRole + 1,
        MeanScoreRole,
        MeanScoreErrRole,
        NumPositionsRole,
        PercentWomenRole,
        PercentWomenErrRole
    };

public:
    explicit ModifiedMartellDataDisplaySummaryTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addLevel(int level, double meanScore, double meanScoreErr,
                  int numPositions, double percentWomen, double percentWomenErr);
    void clearData();

signals:

public slots:

private:
    QList<ModifiedMartellDataDisplaySummaryTableLevel*> m_levels;
};

#endif // MARTELL1996SUMMARYTABLEMODEL_H
