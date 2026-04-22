#ifndef __EmptyTile_h__
#define __EmptyTile_h__

#include "Tile.h"
#include "OutputContext.h"

namespace jb
{

class EmptyTile : public Tile 
{
	virtual bool canOccupy(const jb::OutputContext& context) const { return true; }
};

} // jb

#endif
