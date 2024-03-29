#pragma once

/*!
* \file Scene.h
* 
* \brief Header file for the Scene class.
*/

#include "Core/Internal/AuthorizationBadge.h"

#include "ECS/Entity/GameObject.h"

#define UUID_SYSTEM_GENERATOR
#include "stduuid/uuid.h"

/*!
* \namespace frost::core
*
* \brief The namespace for the FrostEngine core functionalities.
*/
namespace frost::core
{
	class SceneManager;

	/*!
	* \class Scene
	* 
	* \brief In the engine, your game is divided into scenes,
	* and the engine renders the game in the scene that is currently
	* defined as active.
	* 
	* \details Each scene has its own GameObject Tree<T>,
	* on which you can act by adding/removing entities, children of
	* existing GameObjects or by adding/removing components associated
	* with the scene's GameObjects.
	*/
	class FROST_ENGINE_API Scene
	{
	public:

		// Constructors and Destructors
		explicit Scene(const AuthorizationBadge<SceneManager>&, std::string _Name);
		~Scene();

		// Copy and Move Constructors
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
