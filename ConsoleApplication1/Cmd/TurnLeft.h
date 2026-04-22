#ifndef __TurnLeft_h__
#define __TurnLeft_h__

#include "Cmd/Command.h"
#include "OutputContext.h"

namespace jb
{

class Compass;

class CmdTurnLeft : public Command 
{
public:
	CmdTurnLeft(Compass *compass) : m_compass(*compass) { }

	virtual void execute(const jb::OutputContext& context) const override;

private:
	Compass &m_compass;
};

} // jb

#endif
