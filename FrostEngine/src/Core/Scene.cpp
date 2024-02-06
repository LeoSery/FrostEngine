#include "Core/Scene.h"

namespace frost::core
{
	Scene::Scene(std::string _Name)
		: m_name(std::move(_Name)), m_UUID(uuids::uuid_system_generator{}())
	{
	}
}
