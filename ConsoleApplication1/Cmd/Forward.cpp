#include "Cmd/Forward.h"
#include "tile.h"

namespace jb
{

void CmdForward::execute(const jb::OutputContext& context) const
{ 
	Position newPosition = advance(m_position, m_compass);
	if (m_grid.getTile(newPosition.getX(), newPosition.getY()).canOccupy(context))
	{
		context.output("forward\n");
		m_position = newPosition;
	}
	else
	{
		context.output("blocked\n");
	}
}

} // jb
