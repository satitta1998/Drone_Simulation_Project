#include "CmdMap.h"
#include "CharactersMap.h"

#include <iostream>

namespace jb
{
	void CmdMap::execute(const jb::OutputContext& context) const
	{
		extern const CharactersMap characters;

		WorldGrid::const_iterator itr = m_grid.begin(Position{ 0,0 });
		WorldGrid::const_iterator end = m_grid.end(Position{ 0, m_grid.getNumRows() });
		for (; itr != end; ++itr)
		{
			Tile* currentTile = *itr;
			context.output(characters.at(currentTile));

			if (itr.getPos().getX() == m_grid.getRowSize() - 1)
			{
				context.output("\n");
			}
		}
	}
}//jb