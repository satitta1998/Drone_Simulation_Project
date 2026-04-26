#ifndef __ClientManager_h__
#define __ClientManager_h__

#include "Drone.h"

#include <map>
#include <memory>
#include <string>

namespace jb
{
class ClientManager
{
public:

    void addClient(size_t id, std::unique_ptr<Drone> drone);

    void removeClient(size_t id);

    bool exists(size_t id) const;

    bool isActive(size_t id) const;

    Drone* getDrone(size_t id);

    bool& getActiveRef(size_t id);

    bool isClientDronePosition(Position& position) const;

private:
    struct InternalClientState
    {
        std::unique_ptr<Drone> drone;
        bool active = true;
    };

    using ClientMap = std::map<size_t, InternalClientState>;
    ClientMap m_clients;
};

} // jb
#endif
