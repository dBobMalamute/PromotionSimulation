#ifndef MODIFIEDMARTELLDATADISPLAYIDEA_H
#define MODIFIEDMARTELLDATADISPLAYIDEA_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "ModifiedMartellDataType.h"
#include <QtMath>

#include "ModifiedMartellDataDisplaySummaryTableModel.h"

struct ModifiedMartellDataDisplayAttributes : public IdeaAttributes
{
    ModifiedMartellDataDisplayAttributes();
};

class ModifiedMartellDataDisplayIdea : public Idea
{
    Q_OBJECT
public:
    ModifiedMartellDataDisplayIdea();
    const IdeaAttributes attributes() override;

    void finishSetupQmlContext() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;

signals:
    void displayAveragePromotionCycles(double cycles, double stdev);
    void displayNumberRuns(int numRuns);
    void displayTextForCopying(QString text);

private:
    std::weak_ptr<ModifiedMartellDataType> m_input;

    void validate();
    void prepareData();

    ModifiedMartellDataDisplaySummaryTableModel* m_model;
};

#endif // MODIFIEDMARTELLDATADISPLAYIDEA_H
