#include "ngpch.h"
#include "Layer.h"
#include <utility>

namespace engine
{
	
	Layer::Layer(std::string debugName)
		: m_DebugName(std::move(debugName))
	{
		
	}

}