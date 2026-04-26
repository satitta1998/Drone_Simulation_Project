#ifndef __DynamicWorldView_h__
#define __DynamicWorldView_h_

#include "IWorldView.h"
#include "WorldGrid.h"
#include "ClientManager.h"
#include "PlayerTile.h"

namespace jb
{
class DynamicWorldView : public IWorldView
{
public:
	DynamicWorldView(const WorldGrid& theWorld, ClientManager& clients, size_t viewerId)
		: m_grid(theWorld),
		m_clients(clients),
		m_viewerId(viewerId)
	{
	}

	Tile& getTileViewAt(Position& position) const override
	{
		bool isClientDrone = m_clients.isClientDronePosition(position);
		if (isClientDrone)
		{
			return PlayerTile::getInstance();
		}
		return m_grid.getTile(position.getX(), position.getY());
	}

private:
	const WorldGrid& m_grid;
	ClientManager& m_clients;
	size_t m_viewerId;
};
} // jb
#endif