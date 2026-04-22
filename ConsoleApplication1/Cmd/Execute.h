#ifndef __CmdExecute_h__
#define __CmdExecute_h__

#include <functional>
#include "Cmd/Command.h"
#include "OutputContext.h"

namespace jb
{

class CmdExecute : public Command 
{
public:
	CmdExecute(const std::function<void(const jb::OutputContext& context)> &toExecute) : m_toExecute(toExecute) { }
	CmdExecute(const std::function<void(const jb::OutputContext& context)> &&toExecute) : m_toExecute(std::move(toExecute)) { }

	virtual void execute(const jb::OutputContext& context) const override;


private:
	std::function<void(const jb::OutputContext& context)> m_toExecute;
};

} // jb

#endif
