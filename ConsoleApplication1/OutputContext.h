#ifndef __OutputContext_h__
#define __OutputContext_h__
#include "NetworkHandler.h"
#include <string>

namespace jb
{
	class OutputContext
	{
	public:
		OutputContext(whytsoft::NetworkHandler& nh, size_t socketId)
			: m_nh(nh),
			m_socketId(socketId)
		{
		}

		void output(const std::string& str) const;

	private:
		whytsoft::NetworkHandler& m_nh;
		size_t m_socketId;
	};
}// jb
#endif
