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
* \brief The namespace for FrostEngine's core functionalities.
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

		//
		// Constructors and Destructors
		//
		explicit Scene(const AuthorizationBadge<SceneManager>&, std::string _Name);
		~Scene();

		//
		// Copy and Move Constructors
		//
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		Scene(Scene&& _Other) noexcept;
		Scene& operator=(Scene&& _Other) noexcept;

		//
		// Getters
		//

		/*!
		* \brief Get the name of the scene.
		* 
		* \details a string containing the name of the scene.
		* 
		* \fn Scene::GetName() const
		* 
		* \return const std::string&
		*/
		[[nodiscard]] const std::string& GetName() const;

		/*!
		* brief Get the root GameObject of the scene.
		* 
		* \details The root GameObject is the highest parent in the scene.
		* 
		* \fn Scene::GetRoot() const
		* 
		* \return ECS::GameObject*
		*/
		[[nodiscard]] ECS::GameObject* GetRoot() const;

	private:
		uuids::uuid m_uuid;
		std::string m_name;
		ECS::GameObject* m_root;
	};
}
