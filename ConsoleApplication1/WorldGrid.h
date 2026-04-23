#ifndef __WorldGrid_h__
#define __WorldGrid_h__

#include <vector>
#include <array>
#include <fstream>
#include <iterator>
#include "Position.h"
#include "EmptyTile.h"
#include "WallTile.h"
#include "ExitTile.h"
#include "PlayerTile.h"

namespace jb
{
//class WorldGrid;
//extern WorldGrid* GLOBAL_GRID;
class Tile;

extern EmptyTile EMPTY;
extern WallTile WALL;
extern ExitTile EXIT;
extern PlayerTile PLAYER;

class WorldGrid {

public:

	WorldGrid();

	WorldGrid(std::ifstream& inputFile);

	Tile &getTile(int x, int y) const;

	void setTile(int x, int y, Tile& newTile);

	int getNumRows() const { return static_cast<int>(m_grid.size()); }

	int getRowSize() const { return static_cast<int>(m_grid.empty() ? 0 : m_grid.front().size()); }

	class const_iterator;

	const const_iterator begin(const Position& start) const;

	const const_iterator end(const Position& end) const;

private:
	using Row = std::vector<Tile*>;
	using Grid = std::vector<Row>;

	Grid m_grid;
};//WorldGrid

class WorldGrid::const_iterator
{
public:
	const_iterator(const WorldGrid& grid, int x, int y)
		: m_worldGrid(grid),
		m_x(x),
		m_y(y)
	{
	}

	Tile* operator*() const;
	
	const_iterator& operator++();

	bool operator!=(const const_iterator& other) const;

	bool operator==(const const_iterator& other) const;

	Position getPos() const { return Position{ m_x, m_y }; }

private:
	const WorldGrid& m_worldGrid;
	int m_x;
	int m_y;
};

} // jb

#endif
