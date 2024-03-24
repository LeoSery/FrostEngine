#pragma once

#include "Core/Export.h"

#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"

namespace frost::core {
	class Window;
	class Scene;
	class SceneManager;
	
}

namespace frost::ECS {
	class GameObject;
}

namespace frost::utils {
	class Logger;
}


namespace frost::editor
{

	class FROST_ENGINE_API Editor
	{
	public:
		Editor();
		~Editor();

		//Editor(Editor& other) = delete;

		// Singleton
		[[nodiscard]] static Editor* GetInstance();
		static void DeleteEditor();

		// methods //
		int DrawEditor();
		int Init(const frost::core::Window* _Window);
		void Shutdown();

		void DrawHierachyValue(frost::core::Scene* m_CurrentScene);
		void DrawInsperctorValue(frost::ECS::GameObject* m_child);
		
		//example collide
		bool ISCollide = true;

	private:
		static Editor* m_Instance;

		

	};
}
