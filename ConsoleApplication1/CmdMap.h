#ifndef _CmpMap_h_
#define _CmpMap_h_

#include "Cmd/Command.h"
#include "WorldGrid.h"
#include "OutputContext.h"

namespace jb
{
	class CmdMap : public Command
	{
	public:
		CmdMap(const WorldGrid& grid)
			: m_grid(grid)
		{
		}

		virtual void execute(const jb::OutputContext& context) const override;
	private:
		const WorldGrid& m_grid;
	};

} // jb
#endif 
