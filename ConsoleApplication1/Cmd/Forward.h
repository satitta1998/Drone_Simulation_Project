#ifndef __CmdForward_h__
#define __CmdForward_h__

#include <iostream>
#include "Cmd/Command.h"
#include "WorldGrid.h"
#include "Position.h"
#include "Compass.h"
#include "OutputContext.h"

namespace jb
{

class CmdForward : public Command
{
public:
	CmdForward(const WorldGrid *grid, Position *position, const Compass *compass)
		: m_grid(*grid), m_position(*position), m_compass(*compass)
	{ 
	}

	virtual void execute(const jb::OutputContext& context) const override;

private:
	const WorldGrid &m_grid;
	Position &m_position;
	const Compass &m_compass;
};

} // jb

#endif
