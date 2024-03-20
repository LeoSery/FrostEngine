#include "FrostEngine.h"
#include <Core/Input/Input.h>

#include <functional>

namespace FrostEngine
{
	void Application::Init(const InitData& data)
	{
		m_Window = new frost::core::Window({ data.title.c_str(), data.size });
		frost::core::Input::GetInstance()->init(m_Window);
		m_RenderDevice = frost::core::RenderDevice::GetInstance();
		m_RenderDevice->Init(m_Window);
		m_SceneManager = &frost::core::SceneManager::GetInstance();
		m_CurrentScene = &m_SceneManager->GetActiveScene();
	}

	void Application::Run()
	{
		std::chrono::steady_clock::time_point lastUpdateTime = std::chrono::steady_clock::now();

		do
		{
			// Calculate delta time
			auto  now = std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(now - lastUpdateTime).count();
			lastUpdateTime = now;

			// User Update()
			Update(deltaTime);

			// Components Update()
			if (m_CurrentScene != nullptr)
			{
				UpdateObjectComponents(m_CurrentScene->GetRoot(), deltaTime);

				for (auto* child : m_CurrentScene->GetRoot()->GetChildren())
				{
					BrowseAllComponents(child, deltaTime);
				}
			}

			//Physics Update()
			if (m_CurrentScene != nullptr)
			{
				for (auto* child : m_CurrentScene->GetRoot()->GetChildren())
				{
					BrowseAllBoxCollider(child);
				}
			}


			frost::core::Input::GetInstance()->Update();
			// Render Update()
			m_RenderDevice->Update();

			// Logger Update()
			frost::utils::Logger::GetInstance()->Show();

		} while (m_Window->PollEvents());
	}

	void Application::Shutdown()
	{
		delete m_RenderDevice;
		delete m_Window;
	}

	void Application::BrowseAllComponents(frost::ECS::GameObject* _GameObject, float _DeltaTime)
	{
		if (!_GameObject)
			return;

		UpdateObjectComponents(_GameObject, _DeltaTime);

		for (auto* child : _GameObject->GetChildren())
		{
			if (child->IsActive())
				BrowseAllComponents(child, _DeltaTime);
		}
	}

	void Application::UpdateObjectComponents(frost::ECS::GameObject* _GameObject, float _DeltaTime)
	{
		for (auto* component : _GameObject->GetAllComponents())
		{
			if (component->IsActive())
				component->Update(_DeltaTime);
		}
	}

	void Application::BrowseAllBoxCollider(frost::ECS::GameObject* _GameObject)
	{
		if (!_GameObject)
			return;

		for (auto* child : _GameObject->GetChildren())
		{
			if (child->IsActive())
			{
				
			}
		}
	}
}