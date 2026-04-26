#ifndef _MapView_h_
#define _MapView_h_

#include "IWorldView.h"
#include "Position.h"
#include "Compass.h"
#include "OutputContext.h"

namespace jb
{
class MapView
{
public:
	MapView(const IWorldView& grid, Position& position, const Compass& compass)
		: m_grid(grid), m_position(position), m_compass(compass)
	{
	}

	void getView(Position& start, Position& end, const jb::OutputContext& context) const;
private:
	const IWorldView& m_grid;
	Position& m_position;
	const Compass& m_compass;
};

}//jb
#endif 
