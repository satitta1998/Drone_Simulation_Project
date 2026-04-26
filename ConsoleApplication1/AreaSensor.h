#ifndef _AreaSensor_h_
#define _AreaSensor_h_

#include "Sensor.h"
#include "IWorldView.h"
#include "Position.h"
#include "Compass.h"
#include "OutputContext.h"

namespace jb
{
	class AreaSensor : public Sensor
	{
	public:
		AreaSensor() = default;
		virtual void scan(const IWorldView& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const override;
	};

}//jb
#endif 