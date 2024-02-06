#pragma once

#define UUID_SYSTEM_GENERATOR
#include "stduuid/uuid.h"

namespace frost::core
{
	class Scene
	{
	public:
		explicit Scene(std::string _Name);
		~Scene() = default;

	private:
		uuids::uuid m_UUID;
		std::string m_name;
	};
}
