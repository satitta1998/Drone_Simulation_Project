#ifndef __PlayerTile_h__
#define __PlayerTile_h__

#include "Tile.h"
#include "OutputContext.h"

namespace jb
{
struct PlayerTile : public Tile
{
public:
	virtual bool canOccupy(const jb::OutputContext& context) const override { return true; }

	static PlayerTile& getInstance()
	{
		static PlayerTile instance;
		return instance;
	}
};

} // jb
#endif
