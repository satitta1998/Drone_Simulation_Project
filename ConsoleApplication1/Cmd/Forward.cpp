#include "Cmd/Forward.h"
#include "tile.h"

namespace jb
{

void CmdForward::execute(const jb::OutputContext& context) const
{ 
	Position newPosition = advance(m_position, m_compass);
	if (m_grid.getTileViewAt(newPosition).canOccupy(context))
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
