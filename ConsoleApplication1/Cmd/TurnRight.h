#ifndef __TurnRight_h__
#define __TurnRight_h__

#include "Cmd/Command.h"
#include "OutputContext.h"

namespace jb
{

class Compass;

class CmdTurnRight : public Command 
{
public:
	CmdTurnRight(Compass *compass) : m_compass(*compass) { }

	virtual void execute(const jb::OutputContext& context) const override;

private:
	Compass &m_compass;
};

} // jb

#endif
