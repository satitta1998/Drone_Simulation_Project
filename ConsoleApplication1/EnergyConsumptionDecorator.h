#ifndef __EnergyConsumptionDecorator_h__
#define __EnergyConsumptionDecorator_h__

#include "Cmd/Command.h"
#include "OutputContext.h"
#include <memory>

namespace jb
{
class EnergyConsumptionDecorator : public Command
{
public:
	EnergyConsumptionDecorator(std::unique_ptr<Command> cmd,const unsigned int& energyConsumption)
		: m_cmd(std::move(cmd)), m_energyConsumption(energyConsumption)
	{
	}

	void execute(const OutputContext& output) const override
	{
		return m_cmd->execute(output);
	}

	unsigned int getEnergyConsumption() const override
	{
		return m_cmd->getEnergyConsumption() + m_energyConsumption;
	}

private:
	std::unique_ptr<Command> m_cmd;
	const unsigned int m_energyConsumption;
};

} // jb
#endif
