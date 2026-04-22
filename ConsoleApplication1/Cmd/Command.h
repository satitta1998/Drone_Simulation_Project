#ifndef __Command_h__
#define __Command_h__

#include "BaseEssentials.h"
#include "OutputContext.h"

namespace jb
{

struct Command : private BaseEssentials
{
	virtual void execute(const OutputContext &output) const = 0;
	virtual unsigned int getEnergyConsumption() const { return 0; }
};

} // jb

#endif
