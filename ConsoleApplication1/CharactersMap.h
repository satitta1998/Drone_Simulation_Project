#ifndef _CharactersMap_h_
#define _CharactersMap_h_

#include <map>
#include <string>
#include "Tile.h"
#include "OutputContext.h"

namespace jb
{
struct PlayerTile : public Tile {
    virtual bool canOccupy(const jb::OutputContext& context) const override { return true; }
};


struct UnknownTile : public Tile {
    virtual bool canOccupy(const jb::OutputContext& context) const override { return false; }
};

inline PlayerTile PLAYER;
inline UnknownTile UNKNOWN;

using CharactersMap = std::map<Tile*, std::string>;
inline const CharactersMap characters
{
	{&WALL, "#"},
	{&EMPTY, "."},
	{&EXIT, "E"},
	{&PLAYER, "@"},
	{&UNKNOWN, " "}
};
}//jb 
#endif
