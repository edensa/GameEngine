#include "ngpch.h"
#include "UUID.h"

#include <random>


namespace engine
{

    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine(s_RandomDevice());
    static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

    static std::unordered_set<uint64_t> s_IDs;

    UUID::UUID()
        : m_UUID(s_UniformDistribution(s_Engine))
    {
        s_IDs.find(m_UUID);
    }

    UUID::UUID(uint64_t uuid)
        : m_UUID(uuid)
    {

    }

}

namespace std
{

    template<>
	struct hash<engine::UUID>
    {

        std::size_t operator()(const engine::UUID& uuid) const
        {
            return hash<uint64_t>()((uint64_t)uuid);
        }
	    
    };

}
