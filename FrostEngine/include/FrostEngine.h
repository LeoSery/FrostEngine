#pragma once

#include "ECS/Component/Components/SpriteRenderer.h"
#include "ECS/Component/Components/BoxCollider.h"

#include "Core/SceneManagement/SceneManager.h"
#include "Core/Window.h"
#include "Core/Export.h"

#include "Render/RenderDevice.h"
#include "Render/RenderDevice.h"

#include "Utils/Logger.h"
#include "Editor/Editor.h"

#include <chrono>
#include <thread>

namespace FrostEngine
{
	class FROST_ENGINE_API Application
	{
	protected:
		frost::core::Window* m_Window = nullptr;
		frost::core::RenderDevice* m_RenderDevice = nullptr;
		frost::core::SceneManager* m_SceneManager = nullptr;

		frost::core::Scene* m_CurrentScene = nullptr;
		frost::editor::Editor* m_Editor = nullptr;

	public:
		struct InitData
		{
			std::string title;
			glm::ivec2  size;
		};

		// Methods
		virtual void Init() = 0;
		void Init(const InitData& data);

		virtual void Update(float deltaTime) = 0;
		virtual void Shutdown();
		void Run();

	private:
		void BrowseAllGameObjects(frost::ECS::GameObject* _GameObject, float _DeltaTime);
		void PhysUpdate();

		std::vector<frost::ECS::GameObject*> ObjectsToUpdate;
	};

	// Engine life cycle
#define FROST_APPLICATION(ApplicationClass) \
	int main(int argc, char** argv) \
	{ \
		((void)argc); \
		((void)argv); \
		ApplicationClass m_Application; \
		m_Application.Init(); \
		m_Application.Run(); \
		m_Application.Shutdown(); \
		return 0; \
	}
}