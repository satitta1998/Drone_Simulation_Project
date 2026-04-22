#ifndef __Tile_h__
#define __Tile_h__

#include "BaseEssentials.h"
#include "OutputContext.h"

namespace jb
{

class Tile : private BaseEssentials 
{
public:
	enum ExitBehavior { KEEP_GOING, EXIT };
	Tile(ExitBehavior exitBehavior = KEEP_GOING) : m_exitBehavior(exitBehavior) { }

	bool shouldExit() const { return m_exitBehavior == EXIT; }

	virtual bool canOccupy(const jb::OutputContext& context) const = 0;

	//const bool isExitBehavior()
	//{
	//	return (m_exitBehavior == EXIT ? true : false);
	//}

private:
	const ExitBehavior m_exitBehavior;
};

} // jb

#endif
