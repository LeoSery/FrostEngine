#include "FrostEngine.h"

namespace FrostEngine
{
	void Application::Init(const InitData& data)
	{
		m_Window = new frost::core::Window({ data.title.c_str(), data.size });
		m_RenderDevice = new frost::core::RenderDevice(*m_Window);
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

			Update(deltaTime);

			// Main Engine Loop Here

			// temporary render update (replace with SpriteRenderer Update function)
			/////////////////////////////////////////////////////////////
			m_RenderDevice->Update();
			/////////////////////////////////////////////////////////////

			frost::utils::Logger::GetInstance()->Show();
		} while (m_Window->PollEvents());
	}

	void Application::Shutdown()
	{
		delete m_RenderDevice;
		delete m_Window;
		delete m_SceneManager;
	}
}