#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <memory>

#include "Drone.h"
#include "DroneFactory.h"
#include "WorldGrid.h"
#include "Sensor.h"
#include "AreaSensor.h"
#include "StripSensor.h"
#include "ConeSensor.h"
#include "OutputContext.h"
#include "NetworkHandler.h"
#include "SensorRegistry.h"

using namespace jb;

void networkHandlerConnection()
{
    try
    {
        whytsoft::NaiveNetworkHandler nh{ 9000 };
        size_t socketId = 0;
        std::string input;
        bool running = true;

        std::ifstream inputFile("world_grid.txt");
        WorldGrid theWorld{ inputFile };
        inputFile.close();
        
        jb::OutputContext context(nh, socketId);

        jb::registerSensor<AreaSensor>("s_a");
        jb::registerSensor<StripSensor>("s_b");
        jb::registerSensor<ConeSensor>("s_c");

        struct DronConfig
        {
            Position position;
            Compass direction;
            std::vector<Sensor*> sensors;
            unsigned int energy;
        };

        using DronesTypes = std::map < std::string, DronConfig>;
        const DronesTypes drones
        {
            {"Leleka", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_c")}, 300 } },
            {"Shark", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_a"),jb::getSensorPtr("s_b")}, 500 } },
            {"Octopus", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_c")}, 400 }}
        };

        std::cout << "Server started. World loaded." << std::endl;

        std::unique_ptr<Drone> drone = nullptr;
        
        while (drone == nullptr)
        {
            nh.GetInput(&socketId, &input);
            if (input.empty())
            {
                continue;
            }
            if (drones.count(input))
            {
                const DronConfig& cfg = drones.at(input);
                drone = DroneFactory::createCustomDrone(theWorld, cfg.position, cfg.direction, cfg.sensors, cfg.energy, context, running);
                context.output("Drone " + input + " initialized and ready.\n");
            }
            else
            {
                context.output("Unknown drone type! Please choose: Leleka, Shark, or Octopus.\n");
            }
            input.clear();
        }

        while (running)
        {
            nh.GetInput(&socketId, &input);
            if (input.empty())
            {
                continue;
            }

            std::cout << "[Client " << socketId << "]: " << input << std::endl;

            if (!running)
            {
                continue;
            }

            drone->processCommand(input, context, theWorld, running);

            input.clear();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    std::cout << "Server stopped." << std::endl;
}


int main()
{
	networkHandlerConnection();
	return 0;
}
