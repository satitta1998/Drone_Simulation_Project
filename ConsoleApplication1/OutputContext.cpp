#include "OutputContext.h"

namespace jb
{
	void OutputContext::output(const std::string& str) const
	{
		m_nh.PutOutput(m_socketId, str);
	}
}// jb