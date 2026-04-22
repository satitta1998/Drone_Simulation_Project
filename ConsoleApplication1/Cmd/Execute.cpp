#include "Cmd/Execute.h"
#include "Compass.h"
#include "OutputContext.h"
#include <iostream>

namespace jb
{

void CmdExecute::execute(const jb::OutputContext& context) const
{
	m_toExecute(context);
}


} // jb
