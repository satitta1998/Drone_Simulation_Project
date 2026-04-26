#ifndef __DroneFactory_h__
#define __DroneFactory_h__

#include "Drone.h"
#include "WorldGrid.h"
#include "Position.h"
#include "Compass.h"
#include "Sensor.h"
#include "OutputContext.h"
#include "IWorldView.h"

#include <memory>

namespace jb
{
class DroneFactory
{
public:
	static std::unique_ptr<Drone> createCustomDrone(const IWorldView& dynamicWorldView, const WorldGrid& theWorld, Position position, Compass compass, std::vector<Sensor*> sensors, unsigned int energy, const jb::OutputContext& context, bool& working);
};
} // jb
#endif