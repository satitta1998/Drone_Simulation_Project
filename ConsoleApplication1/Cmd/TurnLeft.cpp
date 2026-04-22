#include "Cmd/TurnLeft.h"
#include "Compass.h"
#include <iostream>

namespace jb
{

void CmdTurnLeft::execute(const jb::OutputContext& context) const
{
	turnLeft(&m_compass);
	context.output("turned left. now facing " + std::to_string(m_compass.getHeading()) + "\n");
}


} // jb
