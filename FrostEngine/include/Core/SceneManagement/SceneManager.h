#pragma once

#include "Core/SceneManagement/Scene.h"

namespace frost::core
{
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
