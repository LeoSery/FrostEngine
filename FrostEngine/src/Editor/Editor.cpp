#include "Editor/Editor.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"

#include "Core/Internal/Window.h"

#include "Utils/Logger.h"
#include "Utils/Explorer.h"
#include "ECS/Component/Components/Transform.h"
#include "ECS/Component/Components/SpriteRenderer.h"
#include "ECS/Component/Components/BoxCollider.h"
#include "Render/RenderDevice.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace frost::editor 
{
    Editor* Editor::m_Instance = nullptr;

    Editor::Editor()
    {
    }

    Editor::~Editor()
    {

    }

    Editor* Editor::GetInstance()
    {
        if (!m_Instance)
        {
            m_Instance = new Editor();
        }

        return m_Instance;
    }

    int Editor::DrawEditor()
	{
        frost::core::Scene* m_CurrentScene;
        frost::core::SceneManager* m_SceneManager;

        m_SceneManager = &frost::core::SceneManager::GetInstance();
        m_CurrentScene = &m_SceneManager->GetActiveScene();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        DrawHierarchy(m_CurrentScene);
        DrawInspector();
#ifdef _DEBUG
        DrawConsole();
#endif
        frost::utils::Explorer::GetInstance()->DrawExplorer();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return 0;
	}

    int Editor::Init(const frost::core::Window* _Window)
    {
  
        if (!glfwInit()) {
            return -1;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(_Window->GetInternal()), true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();
        return 0;
    }

    void Editor::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Editor::DrawHierarchy(frost::core::Scene* m_CurrentScene)
    {
        ImGui::SetNextWindowSize(ImVec2(300, 700));
        if (ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoCollapse))

        {
            DrawHierachyValue(m_CurrentScene);
            DrawInsperctorValue();
            ImGui::End();
        }
    }

    void Editor::DrawHierachyValue(frost::core::Scene* m_CurrentScene)
    {
        for(auto* child : m_CurrentScene->GetRoot()->GetChildren())
        {
            if (ImGui::Button(child->GetName().c_str()))
            {
                SelectEntity = child;
            }        
        }
    }

    void Editor::DrawInspector()
    {
        ImGui::SetNextWindowSize(ImVec2(300, 705));
        ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse);
        ImGui::End();

    }

    void Editor::DrawInsperctorValue()
    {
        if (SelectEntity != nullptr)
        {
            if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse))
            {
                frost::ECS::Transform* tr = SelectEntity->GetComponent<frost::ECS::Transform>();
                frost::ECS::SpriteRenderer* sr = SelectEntity->GetComponent<frost::ECS::SpriteRenderer>();              
                frost::ECS::BoxCollider* bc = SelectEntity->GetComponent<frost::ECS::BoxCollider>();

                // Get Transform //
                ImGui::Text("Transform :");
                if (ImGui::InputFloat2("Transform[X/Y]", &tr->position.x))
                {
                    
                }
                
                // Get Rotation //
                if (ImGui::InputFloat2("Rotation", &tr->rotation))
                {

                }
                // Get Scale //
                if (ImGui::InputFloat2("Scale[X / Y]", &tr->scale.x))
                {

                }

                // Get Collider //
                if (ImGui::Checkbox("IsMovingEntity", &tr->isMovingEntity))
                {
                    tr->isMovingEntity = true;
                    if (!tr->isMovingEntity)
                    {
                        tr->isMovingEntity = false;
                    }
                }

                // Get Static //
                ImGui::Text("Path Image : %sr" , sr->GetTexture().c_str());
                bool a = bc->GetIsStatic();
                if (ImGui::Checkbox("IsStatic", &a))
                {
                    a = false;
                    if (!a)
                    {
                        a = true;
                    }
                }
                ImGui::End();
            }
        }

    }
#ifdef _DEBUG
    void Editor::DrawConsole()
    {
        ImGui::SetNextWindowSize(ImVec2(700, 200));
        if (ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoCollapse))
        {
            frost::utils::Logger::GetInstance()->DrawLogger();
            ImGui::End();
        }
    }

    void Editor::DeleteEditor()
    {
        if (m_Instance)
        {
            delete m_Instance;
            m_Instance = nullptr;
        }
    }  
#endif
}