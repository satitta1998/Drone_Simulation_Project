#include "MapView.h"
#include "Position.h"
#include "Compass.h"
#include "CharactersMap.h"

#include <iostream>
#include <string>
#include <iterator>

namespace jb
{
    extern const CharactersMap characters;

	void MapView::getView(Position& start, Position& end, const jb::OutputContext& context) const
	{
        static constexpr int FWD_STEP = 1;
        static constexpr int BWD_STEP = -1;
        static constexpr int STAY_STEP = 0;

        int dx = (end.getX() > start.getX()) ? FWD_STEP : (end.getX() < start.getX() ? BWD_STEP : STAY_STEP);
        int dy = (end.getY() > start.getY()) ? FWD_STEP : (end.getY() < start.getY() ? BWD_STEP : STAY_STEP);

        int steps = (std::max)(std::abs(end.getX() - start.getX()), std::abs(end.getY() - start.getY()));

        Position current = start;

        for (int i = 0; i <= steps; ++i)
        {
            if (current.getX() == m_position.getX() && current.getY() == m_position.getY())
            {
                context.output(characters.at(&PLAYER));
            }
            else
            {
                Tile& tile = m_grid.getTile(current.getX(), current.getY());
                context.output(characters.at(&tile));
            }
            current = Position{ current.getX() + dx, current.getY() + dy };
        }
	}
}// jb