#ifndef __IWorldView_h__
#define __IWorldView_h__

#include "Tile.h"
#include "Position.h"

namespace jb
{
class IWorldView {
public:
    virtual ~IWorldView() = default;

    virtual Tile& getTileViewAt(Position& position) const = 0;
};

} // jb
#endif