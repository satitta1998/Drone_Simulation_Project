#include "Drone.h"
#include "Cmd/Forward.h"
#include "Cmd/TurnLeft.h"
#include "Cmd/TurnRight.h"
#include "Cmd/Execute.h"
#include "CmdPrintPov.h"
#include "CmdMap.h"
#include "Tile.h"

#include "EnergyConsumptionDecorator.h"
#include "EnergyConsumptionValue.h"

namespace jb
{
    using CommandsMap = std::map<std::string, std::unique_ptr<Command>>;

    struct CmdUnknown : public Command
    {
        virtual void execute(const jb::OutputContext& context) const override { context.output("ERROR: Unknown command\n"); }
    } CMD_UNKNOWN;

    Command& parseCommand(const CommandsMap& commands, const std::string& s)
    {
        CommandsMap::const_iterator cmdItr = commands.find(s);
        if (cmdItr == commands.end())
        {
            return CMD_UNKNOWN;
        }
        return *(cmdItr->second);
    }

    Drone::Drone()
        : m_position(Position{0,0}),
        m_compass(Compass{ NORTH }),
        m_availableEnergy(0),
        m_activeSensor(nullptr)
    {
    }

	Drone::Drone(Position position, Compass compass, std::vector<Sensor*>sensors, unsigned int energy, CommandsMap commands, Sensor* activeSensor)
		: m_position(position),
        m_compass(compass),
        m_availableSensors(sensors),
        m_availableEnergy(energy),
        m_commandsMap(std::move(commands)),
        m_activeSensor(activeSensor)
	{
	}

	void Drone::processCommand(const std::string& inputCmd, const jb::OutputContext& context, const WorldGrid& theWorld, bool& running)
	{
        bool isShouldExit = theWorld.getTile(m_position.getX(), m_position.getY()).shouldExit();
        if (isShouldExit) {
            context.output("Target reached. Shutting down.\n");
            m_commandsMap.at("exit")->execute(context);
            return;
        }

        Command& cmd = parseCommand(m_commandsMap, inputCmd);
        unsigned int cost = cmd.getEnergyConsumption();
        if (m_availableEnergy >= cost) {
            cmd.execute(context);
            m_availableEnergy = m_availableEnergy - cost;
            context.output("Energy left: " + std::to_string(m_availableEnergy) + "\n");
        }
        else {
            context.output("NOT ENOUGH ENERGY!\n");
            m_commandsMap.at("exit")->execute(context);
        }
	}
} // jb