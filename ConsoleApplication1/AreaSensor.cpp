#include "AreaSensor.h"
#include "MapView.h"

#include <iostream>
namespace jb
{
	static constexpr int MaxRows = 4;

	void AreaSensor::scan(const WorldGrid& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const
	{
		MapView mapView{ grid, const_cast<Position&>(position), compass };
		Position start = left(back(position, compass), compass);
		
		for (int i = 0; i < MaxRows; ++i)
		{
			Position end = right(right(start, compass), compass);
			mapView.getView(start, end, context);
			context.output("\n");
			start = advance(start, compass);
		}
	}
}// jb