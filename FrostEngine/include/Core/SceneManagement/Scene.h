#pragma once

#include "Core/Internal/AuthorizationBadge.h"
#include "ECS/Entity/GameObject.h"

#define UUID_SYSTEM_GENERATOR
#include "stduuid/uuid.h"

namespace frost::core
{
	class SceneManager;

	class Scene
	{
    public:
        explicit Scene(const AuthorizationBadge<SceneManager>&, std::string _Name);
		~Scene();

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		Scene(Scene&& other) noexcept;
		Scene& operator=(Scene&& other) noexcept;

		const std::string& GetName() const;

		ECS::GameObject* GetRoot() const;

	private:
		uuids::uuid m_UUID;
		std::string m_name;
		ECS::GameObject* m_root;
	};
}
