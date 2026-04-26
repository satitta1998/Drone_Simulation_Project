#include "ConeSensor.h"
#include "MapView.h"
#include "CharactersMap.h"
#include "UnknownTile.h"
#include "PlayerTile.h"
#include <iostream>
#include <string>

namespace jb
{
	static constexpr int MaxDepth = 3;

	static void printRowRecursive(const MapView& view, Position currentPos, const Compass& comp, int currentDepth, int maxDepth, const jb::OutputContext& context)
	{
		if (currentDepth > maxDepth)
			return;

		int spaceNum = maxDepth - currentDepth;
		for (int i = 0; i < spaceNum; ++i)
		{
			context.output(characters.at(&UnknownTile::getInstance()));
		}

		Position start = currentPos;
		Position end = currentPos;
		for (int i = 1; i < currentDepth; ++i) {
			start = left(start, comp);
			end = right(end, comp);
		}

		view.getView(start, end, context);

		context.output("\n");

		printRowRecursive(view, advance(currentPos, comp), comp, currentDepth + 1, maxDepth, context);
	}

	void ConeSensor::scan(const IWorldView& grid, const Position& position, const Compass& compass, const jb::OutputContext& context) const
	{
		MapView mapView{ grid, const_cast<Position&>(position), compass };

		for (int i = 0; i < MaxDepth-1; ++i)
		{
			context.output(characters.at(&UnknownTile::getInstance()));
		}
		context.output(characters.at(&PlayerTile::getInstance()) + "\n");
		
		int currentDepth = 1;
		printRowRecursive(mapView, advance(position, compass), compass, currentDepth, MaxDepth, context);
	}
}// jb