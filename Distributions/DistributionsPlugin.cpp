#include "DistributionsPlugin.h"


#include "GaussianDistributionIdea.h"
#include "DistributionDisplayIdea.h"

#include "../DataTypes/NumberDataType.h"
#include "../DataTypes/DistributionDataType.h"

#include <QQmlEngine>

QString DistributionsPlugin::PluginName()
{
    return "Distribution";
}

QStringList DistributionsPlugin::authors()
{
    return QStringList("dBob");
}

QString DistributionsPlugin::PluginDescription()
{
    return "This plugin holds mathematical distributions";
}

void DistributionsPlugin::registerIdeas(std::shared_ptr<IdeaRegistry> ideaRegistry)
{
    ideaRegistry->registerIdea<GaussianDistributionIdea>();
    ideaRegistry->registerIdea<DistributionDisplayIdea>();

    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/DistributionDisplay.qml"),
                    "com.malamute.distributions", 1, 0, "DistributionDisplay");
}

void DistributionsPlugin::registerDataTypeAttributes(std::shared_ptr<DataTypeRegistry> dataTypeRegistry)
{
    dataTypeRegistry->registerDataTypeAttributes<NumberDataTypeAttributes>();
    dataTypeRegistry->registerDataTypeAttributes<DistributionDataTypeAttributes>();
}

void DistributionsPlugin::registerToolbars(std::shared_ptr<ToolbarRegistry> toolbarRegistry)
{
    QStringList distributionList;
    distributionList << Magic<DistributionDisplayAttributes>::cast().listName();
    distributionList << Magic<GaussianDistributionAttributes>::cast().listName();
    toolbarRegistry->registerToolbar("Distributions", distributionList);
}
