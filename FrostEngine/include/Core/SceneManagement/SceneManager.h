#pragma once

/*!
* \file SceneManager.h
* 
* \brief Header file for the SceneManager class.
*/

#include "Core/SceneManagement/Scene.h"

#include <map>

namespace frost
{
	class Application;
}

namespace frost::ECS
{
	class GameObject;
}

/*!
* \namespace frost::core
*
* \brief The namespace for FrostEngine's core functionalities.
*/
namespace frost::core
{
	/*!
	* \class SceneManager
	* 
	* \brief The SceneManager class is responsible for managing the different scenes in the game.
	* 
	* \details The 'SceneManager' is a singleton that contains a list of scenes in the project,
	* allowing you to define a scene as active and add or remove scenes from the project.
	* It can also return the scene currently active in the engine. 
	*/
	class FROST_ENGINE_API SceneManager
	{
		friend class GameObject;
		friend class Application;

    public:

		// Destructor
        ~SceneManager() = default;

		// Copy and Move
		SceneManager(const SceneManager& _Other) = delete;
		SceneManager(SceneManager&& _Other) noexcept = delete;
		SceneManager& operator=(const SceneManager& _Other) = delete;
		SceneManager& operator=(SceneManager&& _Other) noexcept = delete;

		//  Singleton

		/*!
		* \brief Static method that returns the instance of the SceneManager.
		* 
		* \details This method return the SceneManager isntance.
		* If the instance does not exist, it will create one.
		* 
		* \fn static SceneManager& GetInstance()
		* 
		* \return SceneManager&
		*/
		[[nodiscard]] static SceneManager& GetInstance();

		// Methods

		/*!
		* \brief Method for creating a new scene on the project.
		* 
		* \details This method creates a new scene in the project.
		* 
		* \fn Scene& CreateScene(const std::string& _Name)
		* 
		* \param _Name The name of the scene.
		* 
		* \return Scene&
		*/
		Scene& CreateScene(const std::string& _Name);

		/*
		* \brief Method for removing a scene from the project.
		* 
		* \details This method delete a scene and remove it from the project.
		* 
		* \fn void RemoveScene(const std::string& _SceneName)
		* 
		* \param _SceneName The name of the scene to be removed.
		*/
		void RemoveScene(const std::string& _SceneName);

		/*!
		* \brief Method for loading a scene in the project.
		* 
		* \details This method define a scene as active in the project.
		* 
		* \fn void LoadScene(const std::string& _SceneName)
		*/
		void LoadScene(const std::string& _SceneName);

		// Getters

		/*
		* \brief Method for getting the active scene in the project.
		* 
		* \details This method returns the last scene loaded and currently active in the project.
		* 
		* \fn Scene& GetActiveScene()
		* 
		* \return Scene&
		*/
		[[nodiscard]] Scene& GetActiveScene();
		
		/*!
		* \brief Method for knowing if a GameObject is pending destroy
		* 
		* \details Returns true if the GameObject is in the destruction queue.
		* If it is in the destruction queue, it will be deleted in the next frame
		* during the next engine cycle.
		* 
		* \fn bool IsGameObjectDirty(const uuids::uuid& _UUID) const
		* 
		* \param _UUID The UUID of the GameObject.
		* 
		* \return true if the GameObject is in the destruction queue.
		*/
		bool IsGameObjectDirty(const uuids::uuid& _UUID) const;

		/*
		* \brief Put the GameObject in the destruction queue.
		* 
		* \fn void DestroyGameObject(ECS::GameObject* _GameObject)
		* 
		* \param _GameObject The GameObject to be destroyed.
		*/
		void internalDestroyGameObject(ECS::GameObject* _GameObject);

		/*!
		* \brief Method for destroying all GameObjects in the destruction queue.
		* 
		* \details This method is executed at the start of each engine cycle and
		* destroys all GameObjects that have been placed in the destroy queue.
		* 
		* \fn void DestroyGameObjectQueue()
		*/
		void DestroyGameObjectQueue();
		
	private:
		void AddScene(Scene&& _TargetScene);
		SceneManager() = default;

		std::vector<Scene> m_scenes;
		Scene* m_activeScene = nullptr;

		std::map<uuids::uuid, ECS::GameObject*> m_dirtyGameObjects;

	};
}
