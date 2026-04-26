#ifndef __WallTile_h__
#define __WallTile_h__

#include "Tile.h"
#include "OutputContext.h"

namespace jb
{

class WallTile : public Tile 
{
public:
	virtual bool canOccupy(const jb::OutputContext& context) const { return false; }

	static WallTile& getInstance()
	{
		static WallTile instance;
		return instance;
	}
};

} // jb

#endif
