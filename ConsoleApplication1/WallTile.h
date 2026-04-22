#ifndef __WallTile_h__
#define __WallTile_h__

#include "Tile.h"
#include "OutputContext.h"

namespace jb
{

class WallTile : public Tile 
{
	virtual bool canOccupy(const jb::OutputContext& context) const { return false; }
};

} // jb

#endif
