#include "Core/SceneManagement/SceneManager.h"

#include <vector>

namespace frost::core
{
	SceneManager& frost::core::SceneManager::GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

	Scene& SceneManager::CreateScene(const std::string& _Name)
	{
		AddScene(Scene({}, _Name));
		auto it = std::ranges::find_if(m_scenes, [&](const Scene& _scene) { return _scene.GetName() == _Name; });
		if (it == m_scenes.cend())
			throw std::exception("No scene found");
		return *it;
	}

	void SceneManager::AddScene(Scene&& _TargetScene)
	{
		if (std::ranges::find_if(m_scenes, [&](const Scene& _scene) { return _scene.GetName() == _TargetScene.GetName(); }) != m_scenes.end())
			throw std::runtime_error("Scene with the same name already exists");

		m_scenes.push_back(std::move(_TargetScene));
	}

	void SceneManager::internalDestroyGameObject(ECS::GameObject* _GameObject)
	{
		m_dirtyGameObjects[_GameObject->GetUUID()] = _GameObject;
		_GameObject->SetActive(false);
	}

	void SceneManager::DestroyGameObjectQueue()
	{

		for (auto it = m_dirtyGameObjects.cbegin(); it != m_dirtyGameObjects.cend() /* not hoisted */; /* no increment */)
		{
			it->second->Delete({});
			m_dirtyGameObjects.erase(it++);    // or "it = m.erase(it)" since C++11
		}
	}

	bool SceneManager::IsGameObjectDirty(const uuids::uuid& _UUID) const
	{
		return m_dirtyGameObjects.contains(_UUID);
	}

	void SceneManager::RemoveScene(const std::string& _SceneName)
	{
		const auto it = std::ranges::find_if(m_scenes, [&](const Scene& _scene) { return _scene.GetName() == _SceneName; });

		if (it == m_scenes.end())
			throw std::runtime_error("No scene with this name exists");

		m_scenes.erase(it);
	}

	void SceneManager::LoadScene(const std::string& _SceneName)
	{
		const auto it = std::ranges::find_if(m_scenes, [&](const Scene& _scene) { return _scene.GetName() == _SceneName; });

		if (it == m_scenes.end())
			throw std::runtime_error("No scene with this name exists");

		m_activeScene = &*it;
	}

	Scene& SceneManager::GetActiveScene()
	{
		if (m_activeScene == nullptr)
			throw std::runtime_error("No active scene");

		return *m_activeScene;
	}
}
