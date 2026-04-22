#ifndef __CmdPrintPov_h__
#define __CmdPrintPov_h__

#include "Cmd/Command.h"
#include "WorldGrid.h"
#include "Position.h"
#include "Compass.h"
#include "Sensor.h"

namespace jb
{
	class CmdPrintPov : public Command
	{
	public:
		CmdPrintPov(const WorldGrid* grid, Position* position, const Compass* compass, Sensor** activeSensor)
			: m_grid(*grid), m_position(*position), m_compass(*compass), m_activeSensor(activeSensor)
		{
		}

		virtual void execute(const jb::OutputContext& context) const override;
	private:
		const WorldGrid& m_grid;
		Position& m_position;
		const Compass& m_compass;
		Sensor** m_activeSensor;
	};
} //jb

#endif
