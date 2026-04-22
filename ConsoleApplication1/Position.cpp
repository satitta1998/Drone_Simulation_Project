#include "Position.h"
#include <map>
#include <exception>

namespace jb
{

struct PositionDelta
{
	int deltaX;
	int deltaY;
};

using DeltasMap = std::map<Compass, const PositionDelta>;
static const DeltasMap DELTAS { 
	{ NORTH, { 0, 1 } }, 
	{ EAST, { 1, 0 } }, 
	{ SOUTH, { 0, -1 } }, 
	{ WEST, { -1, 0 } }
};

Position advance(const Position &cur, const Compass &heading)
{
	DeltasMap::const_iterator deltaItr = DELTAS.find(heading);
	if (deltaItr == DELTAS.end())
	{
		throw std::exception{"Unprocessable compass heading"};
	}
	return Position(cur.getX() + deltaItr->second.deltaX, cur.getY() + deltaItr->second.deltaY);
}

Position back(const Position& cur, const Compass& heading)
{
	DeltasMap::const_iterator deltaItr = DELTAS.find(heading);
	if (deltaItr == DELTAS.end())
	{
		throw std::exception{ "Unprocessable compass heading" };
	}

	return Position(cur.getX() - deltaItr->second.deltaX, cur.getY() - deltaItr->second.deltaY);
}

Position right(const Position& cur, const Compass& heading)
{
	DeltasMap::const_iterator deltaItr = DELTAS.find(heading);
	if (deltaItr == DELTAS.end())
	{
		throw std::exception{ "Unprocessable compass heading" };
	}

	return Position(cur.getX() + deltaItr->second.deltaY, cur.getY() - deltaItr->second.deltaX);
}

Position left(const Position& cur, const Compass& heading)
{
	DeltasMap::const_iterator deltaItr = DELTAS.find(heading);
	if (deltaItr == DELTAS.end())
	{
		throw std::exception{ "Unprocessable compass heading" };
	}

	return Position(cur.getX() - deltaItr->second.deltaY, cur.getY() + deltaItr->second.deltaX);
}

} // jb
