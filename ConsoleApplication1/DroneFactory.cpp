#include "DroneFactory.h"
#include "Cmd/Command.h"
#include "Cmd/Forward.h"
#include "Cmd/TurnLeft.h"
#include "Cmd/TurnRight.h"
#include "Cmd/Execute.h"
#include "CmdPrintPov.h"
#include "CmdMap.h"
#include "EnergyConsumptionDecorator.h"
#include "EnergyConsumptionValue.h"
#include "SensorRegistry.h"

#include <map>
#include <typeindex>


namespace jb
{
std::unique_ptr<Drone> DroneFactory::createCustomDrone(const WorldGrid& theWorld, Position position, Compass compass, std::vector<Sensor*> sensors, unsigned int energy, const jb::OutputContext& context, bool& working)
{
	using CommandsMap = std::map<std::string, std::unique_ptr<Command>>;
    
    std::unique_ptr<Drone> drone = std::make_unique<Drone>();

    drone->setPosition(position);
    drone->setCompass(compass);
    drone->setAvailableEnergy(energy);
    drone->setAvailableSensors(sensors);
    drone->setActiveSensor(sensors.front());

    std::unique_ptr<CmdForward> forward = std::make_unique<CmdForward>(&theWorld, &drone->getPosition(), &drone->getCompass());
    std::unique_ptr<CmdTurnLeft> left = std::make_unique<CmdTurnLeft>(&drone->getCompass());
    std::unique_ptr<CmdTurnRight> right = std::make_unique<CmdTurnRight>(&drone->getCompass());
    std::unique_ptr<CmdMap> printMap = std::make_unique<CmdMap>(theWorld);
    std::unique_ptr<CmdExecute> exitLoop = std::make_unique<CmdExecute>([&working](const jb::OutputContext& ctx) { working = false; });
    std::unique_ptr<CmdPrintPov> printPov = std::make_unique<CmdPrintPov>(&theWorld, &drone->getPosition(), &drone->getCompass(), drone->getActiveSensor());

    unsigned int forwardConsumpVal = energyConsumptionValues.at(typeid(*forward));
    unsigned int leftConsumpVal = energyConsumptionValues.at(typeid(*left));
    unsigned int rightConsumpVal = energyConsumptionValues.at(typeid(*right));
    std::unique_ptr<EnergyConsumptionDecorator> forwardWithEnergy = std::make_unique<EnergyConsumptionDecorator>(std::move(forward), forwardConsumpVal);
    std::unique_ptr<EnergyConsumptionDecorator> leftWithEnergy = std::make_unique<EnergyConsumptionDecorator>(std::move(left), leftConsumpVal);
    std::unique_ptr<EnergyConsumptionDecorator> rigthWithEnergy = std::make_unique<EnergyConsumptionDecorator>(std::move(right), rightConsumpVal);
    std::unique_ptr<EnergyConsumptionDecorator> povWithEnergy = std::make_unique<EnergyConsumptionDecorator>(std::move(printPov), energyConsumptionValues.at(typeid(*drone->getActiveSensorValue())));

    CommandsMap commands;
    commands.emplace("fwd", std::move(forwardWithEnergy));
    commands.emplace("+90", std::move(rigthWithEnergy));
    commands.emplace("-90", std::move(leftWithEnergy));
    commands.emplace("exit", std::move(exitLoop));
    commands.emplace("pov", std::move(povWithEnergy));
    commands.emplace("map", std::move(printMap));

    Drone* rawDronePtr = drone.get();
    for (Sensor* s : sensors)
    {
        std::string key = sensorRegistry.at(typeid(*s)).key;
        std::unique_ptr<CmdExecute> selectSensor = std::make_unique<CmdExecute>([rawDronePtr, s](const jb::OutputContext& ctx) { rawDronePtr->setActiveSensor(s); ctx.output("Sensor active\n"); });
        commands.emplace(key, std::move(selectSensor));
    }

    drone->setCommandsMap(std::move(commands));

	return drone;
}
}// jb