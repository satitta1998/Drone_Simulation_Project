#ifndef _CharactersMap_h_
#define _CharactersMap_h_

#include <map>
#include <string>
#include "Tile.h"
#include "OutputContext.h"
#include "UnknownTile.h"

namespace jb
{
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
