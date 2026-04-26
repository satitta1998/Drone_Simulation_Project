#ifndef _ConeSensor_h_
#define _ConeSensor_h_

#include "Sensor.h"
#include "IWorldView.h"
#include "Position.h"
#include "Compass.h"
#include "OutputContext.h"

namespace jb
{
	class ConeSensor : public Sensor
	{
	public:
		ConeSensor() = default;
		virtual void scan(const IWorldView& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const override;
	};

}//jb
#endif 