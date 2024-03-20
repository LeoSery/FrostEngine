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

		//Constructors and Destructors
		explicit Scene(const AuthorizationBadge<SceneManager>&, std::string _Name);
		~Scene();

		//Copy and Move Constructors
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		Scene(Scene&& _Other) noexcept;
		Scene& operator=(Scene&& _Other) noexcept;

		// Getters
		[[nodiscard]] const std::string& GetName() const;
		[[nodiscard]] ECS::GameObject* GetRoot() const;

	private:
		uuids::uuid m_uuid;
		std::string m_name;
		ECS::GameObject* m_root;
	};
}
