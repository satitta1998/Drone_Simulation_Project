#ifndef _StripSensor_h_
#define _StripSensor_h_

#include "Sensor.h"
#include "IWorldView.h"
#include "Position.h"
#include "Compass.h"
#include "OutputContext.h"

namespace jb
{
	class StripSensor : public Sensor
	{
	public:
		StripSensor() = default;
		virtual void scan(const IWorldView& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const override;
	};

}//jb
#endif 