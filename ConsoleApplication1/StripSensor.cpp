#include "StripSensor.h"
#include "CharactersMap.h"
#include "MapView.h"
#include <iostream>
#include <string>

namespace jb
{
	static constexpr int MaxLength = 5;

	void StripSensor::scan(const WorldGrid& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const
	{
		for (int i = 0; i < MaxLength/2; ++i)
		{
			context.output(characters.at(&UNKNOWN));
		}
		context.output(characters.at(&PLAYER) + "\n");

		Position start = advance(position, compass);
		Position end = advance(position, compass);
		for (int i = 0; i < MaxLength / 2; ++i) {
			start = left(start, compass);
			end = right(end, compass);
		}

 		MapView mapView{ grid, const_cast<Position&>(position), compass };
		mapView.getView(start, end, context);
		context.output("\n");
	}
}// jb