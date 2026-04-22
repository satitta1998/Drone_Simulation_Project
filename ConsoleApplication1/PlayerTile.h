#ifndef __PlayerTile_h__
#define __PlayerTile_h__

#include "Tile.h"
#include "OutputContext.h"

namespace jb
{
struct PlayerTile : public Tile
{
	virtual bool canOccupy(const jb::OutputContext& context) const override { return true; }
};

} // jb
#endif
