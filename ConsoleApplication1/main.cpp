#include <iostream>
#include <string>
#include <string_view>
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

        AreaSensor s_a;
        StripSensor s_b;
        ConeSensor s_c;

        std::unique_ptr<Drone> drone = DroneFactory::createCustomDrone(theWorld, Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{&s_a, & s_b}, 1000, context, running);

        std::cout << "Server started. World loaded." << std::endl;

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
