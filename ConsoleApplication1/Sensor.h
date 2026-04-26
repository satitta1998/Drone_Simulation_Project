#ifndef _Sensor_h_
#define _Sensor_h_

#include "IWorldView.h"
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
	virtual void scan(const IWorldView& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const = 0;
};
} // jb
#endif
