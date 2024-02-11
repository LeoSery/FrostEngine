#include "Core/SceneManager.h"

#include <vector>

namespace frost::core
{
	SceneManager& frost::core::SceneManager::GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

	void SceneManager::AddScene(Scene&& _TargetScene)
	{
		if (std::ranges::find_if(m_Scenes, [&](const Scene& _scene) { return _scene.GetName() == _TargetScene.GetName(); }) != m_Scenes.end())
			throw std::runtime_error("Scene with the same name already exists");

		m_Scenes.push_back(std::move(_TargetScene));
	}

	void SceneManager::RemoveScene(const std::string& _SceneName)
	{
		const auto it = std::ranges::find_if(m_Scenes, [&](const Scene& _scene) { return _scene.GetName() == _SceneName; });

		if (it == m_Scenes.end())
			throw std::runtime_error("No scene with this name exists");

		m_Scenes.erase(it);
	}

	void SceneManager::LoadScene(const std::string& _SceneName)
	{
		const auto it = std::ranges::find_if(m_Scenes, [&](const Scene& _scene) { return _scene.GetName() == _SceneName; });

		if (it == m_Scenes.end())
			throw std::runtime_error("No scene with this name exists");

		m_ActiveScene = &*it;
	}

	Scene& SceneManager::GetActiveScene()
	{
		if (m_ActiveScene == nullptr)
			throw std::runtime_error("No active scene");

		return *m_ActiveScene;
	}
}
