#ifndef _Sensor_h_
#define _Sensor_h_

#include "WorldGrid.h"
#include "Position.h"
#include "Compass.h"
#include "OutputContext.h"

namespace jb
{
class Sensor // Base class
{
public:
	Sensor() = default;
	virtual ~Sensor() = default;
	virtual void scan(const WorldGrid& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const = 0;
};
} // jb
#endif
