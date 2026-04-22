#ifndef _ConeSensor_h_
#define _ConeSensor_h_

#include "Sensor.h"
#include "WorldGrid.h"
#include "Position.h"
#include "Compass.h"
#include "OutputContext.h"

namespace jb
{
	class ConeSensor : public Sensor
	{
	public:
		ConeSensor() = default;
		virtual void scan(const WorldGrid& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const override;
	};

}//jb
#endif 