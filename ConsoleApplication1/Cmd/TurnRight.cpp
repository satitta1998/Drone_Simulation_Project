#include "Cmd/TurnRight.h"
#include "Compass.h"
#include <iostream>

namespace jb
{

void CmdTurnRight::execute(const jb::OutputContext& context) const
{
	turnRight(&m_compass);
	context.output("turned right. now facing " + std::to_string(m_compass.getHeading()) + "\n");
}


} // jb
