#ifndef _CharactersMap_h_
#define _CharactersMap_h_

#include <map>
#include <string>
#include "Tile.h"
#include "OutputContext.h"
#include "UnknownTile.h"
#include "EmptyTile.h"
#include "WallTile.h"
#include "ExitTile.h"
#include "PlayerTile.h"

namespace jb
{

using CharactersMap = std::map<Tile*, std::string>;
inline const CharactersMap characters
{
	{&WallTile::getInstance(), "#"},
	{&EmptyTile::getInstance(), "."},
	{&ExitTile::getInstance(), "E"},
	{&PlayerTile::getInstance(), "@"},
	{&UnknownTile::getInstance(), " "}
};
}//jb 
#endif
