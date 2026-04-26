#include "ClientManager.h"

namespace jb
{
    void ClientManager::addClient(size_t id, std::unique_ptr<Drone> drone)
    {
        m_clients[id] = InternalClientState{ std::move(drone), true };
    }

    void ClientManager::removeClient(size_t id)
    {
        m_clients.erase(id);
    }

    bool ClientManager::exists(size_t id) const
    {
        return m_clients.find(id) != m_clients.end();
    }

    bool ClientManager::isActive(size_t id) const
    {
        ClientMap::const_iterator it = m_clients.find(id);
        if (it != m_clients.end()) {
            return it->second.active;
        }
        return false;
    }

    Drone* ClientManager::getDrone(size_t id)
    {
        return m_clients.at(id).drone.get();
    }

    bool& ClientManager::getActiveRef(size_t id)
    {
        return m_clients.at(id).active;
    }

    bool ClientManager::isClientDronePosition(Position& position) const
    {
        ClientMap::const_iterator itr = m_clients.begin();
        for (; itr != m_clients.end(); ++itr)
        {
            if (itr->second.active && itr->second.drone->getPosition().getX() == position.getX() && itr->second.drone->getPosition().getY() == position.getY())
            {
                return true;
            }
        }
        return false;
    }

} // jb