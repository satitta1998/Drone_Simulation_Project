#ifndef __EnergyConsumptionValue_h__
#define __EnergyConsumptionValue_h__

#include <typeindex>
#include <map>
#include "Cmd/Forward.h"
#include "Cmd/TurnLeft.h"
#include "Cmd/TurnRight.h"
#include "AreaSensor.h"
#include "StripSensor.h"
#include "ConeSensor.h"

namespace jb
{
using EnergyConsumptionValue = std::map < std::type_index, unsigned int > ;
inline const EnergyConsumptionValue energyConsumptionValues
{
	{typeid(CmdForward), 5},
	{typeid(CmdTurnLeft), 4},
	{typeid(CmdTurnRight), 4},
	{typeid(AreaSensor), 3},
	{typeid(StripSensor), 1},
	{typeid(ConeSensor), 2}
};

} // jb
#endif