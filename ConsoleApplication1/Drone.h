#ifndef __Drone_h__
#define __Drone_h__

#include "WorldGrid.h"
#include "Compass.h"
#include "Sensor.h"
#include "Position.h"
#include "OutputContext.h"
#include "Cmd/Command.h"

#include <vector>
#include <map>
#include <memory>

namespace jb
{

class Drone
{
public:
	using CommandsMap = std::map<std::string, std::unique_ptr<Command>>;

	Drone();
	
	explicit Drone(Position position,Compass compass, std::vector<Sensor*>sensors, unsigned int energy, CommandsMap commands, Sensor* activeSensor);

	void processCommand(const std::string& inputCmd, const jb::OutputContext& context, const WorldGrid& theWorld, bool& running);

	void setPosition(Position& position) { m_position = position; }
	void setCompass(Compass& compass) { m_compass = compass; }
	void setAvailableSensors(std::vector<Sensor*> sensors) { m_availableSensors = sensors; }
	void setAvailableEnergy(unsigned int energy) { m_availableEnergy = energy; }
	void setCommandsMap(CommandsMap commands) { m_commandsMap = std::move(commands); }
	void setActiveSensor(Sensor* activeSensor) { m_activeSensor = activeSensor; }

	Position& getPosition() { return m_position; }
	Compass& getCompass() { return m_compass; }
	Sensor** getActiveSensor() { return &m_activeSensor; }
	Sensor* getActiveSensorValue() const { return m_activeSensor; }

private:
	Position m_position;
	Compass m_compass;
	std::vector<Sensor*> m_availableSensors;
	unsigned int m_availableEnergy;
	CommandsMap m_commandsMap;
	Sensor* m_activeSensor;
};

} // jb

#endif
