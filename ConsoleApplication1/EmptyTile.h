#ifndef __EmptyTile_h__
#define __EmptyTile_h__

#include "Tile.h"
#include "OutputContext.h"

namespace jb
{

class EmptyTile : public Tile 
{
public:
	virtual bool canOccupy(const jb::OutputContext& context) const { return true; }

	static EmptyTile& getInstance()
	{
		static EmptyTile instance;
		return instance;
	}
};

} // jb

#endif
