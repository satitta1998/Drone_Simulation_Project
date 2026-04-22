#ifndef _StripSensor_h_
#define _StripSensor_h_

#include "Sensor.h"
#include "WorldGrid.h"
#include "Position.h"
#include "Compass.h"
#include "OutputContext.h"

namespace jb
{
	class StripSensor : public Sensor
	{
	public:
		StripSensor() = default;
		virtual void scan(const WorldGrid& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const override;
	};

}//jb
#endif 