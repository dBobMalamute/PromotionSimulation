#ifndef SIMULATIONMODE_H
#define SIMULATIONMODE_H

#include <QObject>

class SimulationMode : public QObject
{
    Q_OBJECT
public:
    SimulationMode();

    enum SimulationModeEnum
    {
        NORMAL,
        ANIMATE,
        BULK
    };

    Q_ENUM(SimulationModeEnum);
};

#endif // SIMULATIONMODE_H
