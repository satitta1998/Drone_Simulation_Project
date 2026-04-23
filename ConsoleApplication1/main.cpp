#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <memory>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

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

struct InputEvent
{
    size_t socketId;
    std::string input;
};

std::queue<InputEvent> g_queue;
std::mutex g_mutex;
std::condition_variable g_cv;

void readerThread(whytsoft::NaiveNetworkHandler& nh, bool& running)
{
    while (running)
    {
        size_t socketId = 0;
        std::string input;

        nh.GetInput(&socketId, &input);
        if (!input.empty())
        {
            std::lock_guard<std::mutex> lockOnInputEventQueue(g_mutex);
            g_queue.push({ socketId, input });
            g_cv.notify_one();
        }
    }
}

int main()
{
    try
    {
        whytsoft::NaiveNetworkHandler nh{ 9000 };
        bool running = true;

        std::thread reader(readerThread, std::ref(nh), std::ref(running));
        
        std::ifstream inputFile("world_grid.txt");
        if (!inputFile)
        {
            std::cerr << "Failed to open world grid file.\n" << std::endl;
            return 1;
        }
        WorldGrid theWorld{ inputFile };
        inputFile.close();

        jb::registerSensor<AreaSensor>("s_a");
        jb::registerSensor<StripSensor>("s_b");
        jb::registerSensor<ConeSensor>("s_c");

        struct DroneConfig
        {
            Position position;
            Compass direction;
            std::vector<Sensor*> sensors;
            unsigned int energy;
        };

        using DronesTypes = std::map < std::string, DroneConfig>;
        const DronesTypes drones
        {
            {"Leleka", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_c")}, 300 } },
            {"Shark", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_a"),jb::getSensorPtr("s_b")}, 500 } },
            {"Octopus", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_c")}, 400 }}
        };

        struct ClientState
        {
            std::unique_ptr<Drone> drone;
            bool active = true;
        };
        using ClientsMap = std::map<size_t, ClientState>;
        ClientsMap clients;

        std::cout << "Server started. World loaded." << std::endl;

        while (running)
        {
            std::unique_lock<std::mutex> lockOnQueue(g_mutex);
            g_cv.wait(lockOnQueue, [] {return !g_queue.empty(); });

            InputEvent ev = std::move(g_queue.front());
            g_queue.pop();
            lockOnQueue.unlock();

            size_t socketId = ev.socketId;
            std::string input = ev.input;

            OutputContext context(nh, socketId);

            auto itr = clients.find(socketId);
            bool isNewClient = itr == clients.end();
            if (isNewClient)
            {
                if (drones.count(input))
                {
                    const DroneConfig& cfg = drones.at(input);
                    ClientState state;
                    state.drone = DroneFactory::createCustomDrone(theWorld, cfg.position, cfg.direction, cfg.sensors, cfg.energy, context, running);
                    clients[socketId] = std::move(state);
                    context.output("Drone " + input + " assigned to you (ID: " + std::to_string(socketId) + "). Ready.\n");
                }
                else
                {
                    context.output("Welcome! Please choose your drone: Leleka, Shark, or Octopus.\n");
                }
                continue;
            }
            ClientState& client = itr->second;
            Drone* drone = client.drone.get();
            if (!client.active)
            {
                clients.erase(socketId);
                continue;
            }
            std::cout << "[Client " << socketId << "]: " << input << std::endl;
            drone->processCommand(input, context, theWorld, running);
            input.clear();
        }
        running = false;
        g_cv.notify_all();
        if (reader.joinable())
        {
            reader.join();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    std::cout << "Server stopped." << std::endl;
    return 0;
}

///* WORKING VERSION FOR 1 DRONE */
//void networkHandlerConnection()
//{
//    try
//    {
//        whytsoft::NaiveNetworkHandler nh{ 9000 };
//        size_t socketId = 0;
//        std::string input;
//        bool running = true;
//
//        std::ifstream inputFile("world_grid.txt");
//        WorldGrid theWorld{ inputFile };
//        inputFile.close();
//
//        OutputContext context(nh, socketId);
//
//        jb::registerSensor<AreaSensor>("s_a");
//        jb::registerSensor<StripSensor>("s_b");
//        jb::registerSensor<ConeSensor>("s_c");
//
//        struct DronConfig
//        {
//            Position position;
//            Compass direction;
//            std::vector<Sensor*> sensors;
//            unsigned int energy;
//        };
//
//        using DronesTypes = std::map < std::string, DronConfig>;
//        const DronesTypes drones
//        {
//            {"Leleka", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_c")}, 300 } },
//            {"Shark", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_a"),jb::getSensorPtr("s_b")}, 500 } },
//            {"Octopus", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_c")}, 400 }}
//        };
//        
//        std::unique_ptr<Drone> drone = nullptr;
//        
//        while (drone == nullptr)
//        {
//            nh.GetInput(&socketId, &input);
//            if (input.empty())
//            {
//                continue;
//            }
//            if (drones.count(input))
//            {
//                const DronConfig& cfg = drones.at(input);
//                drone = DroneFactory::createCustomDrone(theWorld, cfg.position, cfg.direction, cfg.sensors, cfg.energy, context, running);
//                context.output("Drone " + input + " initialized and ready.\n");
//            }
//            else
//            {
//                context.output("Unknown drone type! Please choose: Leleka, Shark, or Octopus.\n");
//            }
//            input.clear();
//        }
//        while (running)
//        {
//            nh.GetInput(&socketId, &input);
//            if (input.empty())
//            {
//                continue;
//            }
//            std::cout << "[Client " << socketId << "]: " << input << std::endl;
//            if (!running)
//            {
//                continue;
//            }
//            drone->processCommand(input, context, theWorld, running);
//            input.clear();
//        }
//
//    }
//    catch (const std::exception& e)
//    {
//        std::cerr << "Runtime error: " << e.what() << std::endl;
//    }
//    std::cout << "Server stopped." << std::endl;
//}
//
//
//int main()
//{
//	networkHandlerConnection();
//	return 0;
//}
