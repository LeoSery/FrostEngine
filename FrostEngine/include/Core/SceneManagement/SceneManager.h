#pragma once

#include "Core/SceneManagement/Scene.h"

namespace frost::core
{
	class FROST_ENGINE_API SceneManager
	{
    public:
        ~SceneManager() = default;
		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) noexcept = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) noexcept = delete;

		[[nodiscard]] static SceneManager& GetInstance();

		Scene& CreateScene(const std::string& _Name);

		void RemoveScene(const std::string& _SceneName);

		void LoadScene(const std::string& _SceneName);

		[[nodiscard]] Scene& GetActiveScene();

	private:
		void AddScene(Scene&& _TargetScene);

		SceneManager() = default;
		std::vector<Scene> m_Scenes;
		Scene* m_ActiveScene = nullptr;
	};
}
