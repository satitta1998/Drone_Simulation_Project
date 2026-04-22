#ifndef __ExitTile_h__
#define __ExitTile_h__

#include "Tile.h"
#include "OutputContext.h"

namespace jb
{

struct ExitTile : public Tile 
{
	ExitTile() : Tile(EXIT) { }
	virtual bool canOccupy(const jb::OutputContext& context) const { return true; }
};

} // jb

#endif
