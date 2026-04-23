#include "WorldGrid.h"
#include "CharactersMap.h"
#include "Tile.h"
#include <iostream>
#include <string>
#include <map>

namespace jb
{
WorldGrid* GLOBAL_GRID = nullptr;
using CharMap = std::map<char, Tile*>;
Tile& parseCharacters(const CharactersMap& characters, const char& ch);

struct ChUnknown : public Tile
{
	virtual bool canOccupy(const jb::OutputContext& context) const override { context.output("ERROR: Unknown character\n"); return false; }
} CH_UNKNOWN;

EmptyTile EMPTY{};
WallTile WALL{};
ExitTile EXIT{};
PlayerTile PLAYER{};

WorldGrid::WorldGrid() 
	: m_grid{}
{ 
	                                             // =======  
	m_grid[0][0] = &WALL;                        // = #   =
	m_grid[1][1] = &WALL;                        // = #   =
	m_grid[2][2] = &WALL;                        // =  #  =   |
	m_grid[3][3] = &WALL;                        // =   # =   |
	m_grid[4][0] = &WALL; m_grid[4][3] = &WALL;  // =#   #=  \|/
	m_grid[5][1] = &WALL; m_grid[5][4] = &EXIT;  // = #  E=   N
	                                             // =======
}

WorldGrid::WorldGrid(std::ifstream& inputFile)
	: m_grid()
{
	char ch;
	Row currentRow;
	while (inputFile.get(ch))
	{
		if (ch == '\n')
		{
			m_grid.push_back(currentRow);
			currentRow.clear();
			continue;
		}

		Tile& tile = parseCharacters(characters, ch);
		currentRow.push_back(&tile);
	}
	// If the file doesn't end with a newline, add the last row
	if (!currentRow.empty())
	{
		m_grid.push_back(currentRow);
	}
}

Tile &WorldGrid::getTile(int x, int y) const
{
	if (x < 0 || y < 0)
	{
		return WALL;
	}
	if (x >= getRowSize() || y >= getNumRows())
	{
		return WALL;
	}

	Tile *tile = m_grid[y][x];
	return tile ? *tile : EMPTY;
}

void WorldGrid::setTile(int x, int y, Tile& newTile)
{
	m_grid[y][x] = &newTile;
}

Tile& parseCharacters(const CharactersMap& characters, const char& ch)
{
	std::string searchStr(1, ch);

	for (CharactersMap::const_iterator it = characters.begin(); it != characters.end(); ++it)
	{
		if (it->second == searchStr)
		{
			return *(it->first);
		}
	}
	return CH_UNKNOWN;
}

const WorldGrid::const_iterator WorldGrid::begin(const Position& start) const
{
	return const_iterator(*this, start.getX(), start.getY());
}

const WorldGrid::const_iterator WorldGrid::end(const Position& end) const
{
	return const_iterator(*this, end.getX(), end.getY());
}

WorldGrid::const_iterator& WorldGrid::const_iterator::operator++()
{
	if (m_x < m_worldGrid.getRowSize() - 1)
	{
		++m_x;
	}
	else
	{
		++m_y;
		m_x = 0;
	}
	return *this;
};


Tile* WorldGrid::const_iterator::operator*() const
{ 
	return &m_worldGrid.getTile(m_x, m_y);
};

bool WorldGrid::const_iterator::operator!=(const WorldGrid::const_iterator& other) const
{
	return (&m_worldGrid != &other.m_worldGrid || this->m_x != other.m_x || this->m_y != other.m_y);
}

bool WorldGrid::const_iterator::operator==(const WorldGrid::const_iterator& other) const
{
	return !operator!=(other);
}

} // jb
