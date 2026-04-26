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
#include "ClientManager.h"
#include "DynamicWorldView.h"

using namespace jb;

struct InputEvent
{
    size_t socketId;
    std::string input;
};

struct EventQueue {
    std::queue<InputEvent> queue;
    std::mutex mutex;
    std::condition_variable cv;
};

struct DroneConfig
{
    Position position;
    Compass direction;
    std::vector<Sensor*> sensors;
    unsigned int energy;
};

struct ThreadReader
{
public:
    ThreadReader(whytsoft::NaiveNetworkHandler& nh, bool& running, EventQueue& eq)
        : m_nh(nh),
        m_running(running),
        m_eq(eq)
    {
    }

    void operator()() const
    {
        while (m_running)
        {
            size_t socketId = 0;
            std::string input;

            m_nh.GetInput(&socketId, &input);
            if (!input.empty())
            {
                std::lock_guard<std::mutex> lockOnInputEventQueue(m_eq.mutex);
                m_eq.queue.push({ socketId, input });
                m_eq.cv.notify_one();
            }
        }
    }

private:
    whytsoft::NaiveNetworkHandler& m_nh;
    bool& m_running;
    EventQueue& m_eq;
};

WorldGrid setupEnvironment()
{
    std::ifstream inputFile("world_grid.txt");
    if (!inputFile)
    {
        throw std::exception{ "Failed to open world grid file." };
    }
    WorldGrid theWorld{ inputFile };
    inputFile.close();
    return theWorld;
}

int main()
{
    try
    {
        whytsoft::NaiveNetworkHandler nh{ 9000 };
        bool serverRunning = true;
        EventQueue eventQueue;

        ThreadReader readerFunctor(nh, serverRunning, eventQueue);
        std::thread reader(std::ref(readerFunctor));

        WorldGrid theWorld = setupEnvironment();

        jb::registerSensor<AreaSensor>("s_a");
        jb::registerSensor<StripSensor>("s_b");
        jb::registerSensor<ConeSensor>("s_c");

        using DronesTypes = std::map < std::string, DroneConfig>;
        const DronesTypes drones
        {
            {"Leleka", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_c")}, 300 } },
            {"Shark", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_a"),jb::getSensorPtr("s_b")}, 500 } },
            {"Octopus", { Position{ 0,0 }, Compass{ NORTH }, std::vector<Sensor*>{jb::getSensorPtr("s_c")}, 400 }}
        };

        ClientManager clients;

        std::cout << "Server started. World loaded." << std::endl;

        while (serverRunning)
        {
            std::unique_lock<std::mutex> lockOnQueue(eventQueue.mutex);
            eventQueue.cv.wait(lockOnQueue, [&] {return !eventQueue.queue.empty() || !serverRunning; });

            InputEvent ev = std::move(eventQueue.queue.front());
            eventQueue.queue.pop();
            lockOnQueue.unlock();

            size_t socketId = ev.socketId;
            std::string input = ev.input;

            OutputContext context(nh, socketId);

            if (input == "exit")
            {
                clients.removeClient(socketId);
                std::cout << "Client " << socketId << " disconnected\n";
                nh.disconnect(socketId);
                continue;
            }

            DynamicWorldView worldView{ theWorld, clients, socketId };

            if (!clients.exists(socketId))
            {
                if (drones.count(input))
                {
                    const DroneConfig& cfg = drones.at(input);
                    bool initialActive = true;
                    std::unique_ptr<Drone> newDrone = DroneFactory::createCustomDrone(worldView, theWorld, cfg.position, cfg.direction, cfg.sensors, cfg.energy, context, initialActive);
                    clients.addClient(socketId, std::move(newDrone));
                    context.output("Drone " + input + " assigned to you (ID: " + std::to_string(socketId) + "). Ready.\n");
                }
                else
                {
                    context.output("Please choose your drone: Leleka, Shark, or Octopus.\n");
                }
                continue;
            }

            if (!clients.isActive(socketId))
            {
                clients.removeClient(socketId);
                continue;
            }

            Drone* drone = clients.getDrone(socketId);
            bool& activeRef = clients.getActiveRef(socketId);

            std::cout << "[Client " << socketId << "]: " << input << std::endl;
            drone->processCommand(input, context, theWorld, activeRef);
            input.clear();
        }
        serverRunning = false;
        eventQueue.cv.notify_all();
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
