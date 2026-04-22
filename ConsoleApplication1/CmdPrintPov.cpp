#include "CmdPrintPov.h"
#include "AreaSensor.h"
#include "StripSensor.h"
#include "ConeSensor.h"

namespace jb
{
	void CmdPrintPov::execute(const jb::OutputContext& context) const
	{
        (*m_activeSensor)->scan(m_grid, m_position, m_compass, context);
	}
} //jb