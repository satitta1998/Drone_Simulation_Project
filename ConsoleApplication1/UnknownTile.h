#ifndef __UnknownTile_h__
#define __UnknownTile_h__

#include "Tile.h"
#include "OutputContext.h"

namespace jb
{
struct UnknownTile : public Tile
{
public:
	virtual bool canOccupy(const jb::OutputContext& context) const override { return false; }

	static UnknownTile& getInstance()
	{
		static UnknownTile instance;
		return instance;
	}
};

} // jb
#endif
