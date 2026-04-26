#ifndef __ExitTile_h__
#define __ExitTile_h__

#include "Tile.h"
#include "OutputContext.h"

namespace jb
{

struct ExitTile : public Tile 
{
public:
	ExitTile() : Tile(EXIT) { }
	virtual bool canOccupy(const jb::OutputContext& context) const { return true; }

	static ExitTile& getInstance()
	{
		static ExitTile instance;
		return instance;
	}
};

} // jb

#endif
