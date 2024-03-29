#pragma once

/*!
* \file SceneManager.h
* 
* \brief Header file for the SceneManager class.
*/

#include "Core/SceneManagement/Scene.h"

/*!
* \namespace frost::core
*
* \brief The namespace for the FrostEngine core functionalities.
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
    public:

		// Destructor
        ~SceneManager() = default;

		// Copy and Move
		SceneManager(const SceneManager& _Other) = delete;
		SceneManager(SceneManager&& _Other) noexcept = delete;
		SceneManager& operator=(const SceneManager& _Other) = delete;
		SceneManager& operator=(SceneManager&& _Other) noexcept = delete;

		//  Singleton
		[[nodiscard]] static SceneManager& GetInstance();

		// Methods
		Scene& CreateScene(const std::string& _Name);
		void RemoveScene(const std::string& _SceneName);
		void LoadScene(const std::string& _SceneName);

		// Getters
		[[nodiscard]] Scene& GetActiveScene();

	private:
		void AddScene(Scene&& _TargetScene);
		SceneManager() = default;

		std::vector<Scene> m_scenes;
		Scene* m_activeScene = nullptr;
	};
}
