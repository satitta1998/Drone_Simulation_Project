#include "StripSensor.h"
#include "CharactersMap.h"
#include "UnknownTile.h"
#include "PlayerTile.h"
#include "MapView.h"
#include <iostream>
#include <string>

namespace jb
{
	static constexpr int MaxLength = 5;

	void StripSensor::scan(const IWorldView& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const
	{
		for (int i = 0; i < MaxLength/2; ++i)
		{
			context.output(characters.at(&UnknownTile::getInstance()));
		}
		context.output(characters.at(&PlayerTile::getInstance()) + "\n");

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