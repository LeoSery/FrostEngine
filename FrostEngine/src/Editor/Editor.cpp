#include "Editor/Editor.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"

#include "Core/Internal/Window.h"

#include "Utils/Logger.h"
#include "Utils/Explorer.h"
#include "Utils/TextEditor.h"
#include "ECS/Component/Components/Transform.h"
#include "ECS/Component/Components/SpriteRenderer.h"
#include "ECS/Component/Components/BoxCollider.h"
#include "ECS/Entity/GameObject.h"
#include "Render/RenderDevice.h"
#include "FrostEngine.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace frost::editor 
{
    Editor* Editor::m_instance = nullptr;

    Editor::Editor()
    {
    }

    Editor::~Editor()
    {
        //DeleteEditor();
    }

    Editor* Editor::GetInstance()
    {
        if (!m_instance)
        {
            m_instance = new Editor();
        }

        return m_instance;
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

#ifdef _DEBUG     
        DrawHierarchy(m_CurrentScene);
        DrawInspector();
        frost::utils::Explorer::GetInstance()->DrawExplorer();
        //frost::utils::TextEditor::GetInstance()->DrawTextEditor();
#endif      

#if defined _DEBUG || _QA
        DrawConsole();
        DrawFps();
#endif

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

        ImGui::GetIO().Framerate;
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

    frost::ECS::GameObject* Editor::GetSelectEntity()
    {
        return m_selectEntity;
    }

    void Editor::SetSelectEntity(frost::ECS::GameObject* _Entity)
    {
       m_selectEntity = _Entity;
    }

    void Editor::DrawHierarchy(frost::core::Scene* _CurrentScene)
    {
        ImGui::SetNextWindowSize(ImVec2(300, 700));
        if (ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoCollapse))

        {
            DrawHierachyValue(_CurrentScene);
            DrawInsperctorValue();
            ImGui::End();
        }
    }

    void Editor::DrawHierachyValue(frost::core::Scene* _CurrentScene)
    {
        for(auto* child : _CurrentScene->GetRoot()->GetChildren())
        {
            if (child != nullptr)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(35, 68, 108, 1));
                if (ImGui::Button(child->GetName().c_str()))
                {
                    m_selectEntity = child;
                }  
                ImGui::PopStyleColor();
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
        if (m_selectEntity != nullptr)
        {
            if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse))
            {
                frost::ECS::Transform* tr = m_selectEntity->GetComponent<frost::ECS::Transform>();
                frost::ECS::SpriteRenderer* sr = m_selectEntity->GetComponent<frost::ECS::SpriteRenderer>();              
                frost::ECS::BoxCollider* bc = m_selectEntity->GetComponent<frost::ECS::BoxCollider>();
                
                if (m_selectEntity == nullptr)
                {
					ImGui::Text("No Object Selected");
					ImGui::End();
					return;
				}

                // Get Name //
                std::string name = m_selectEntity->GetName().c_str();              
                float font_size = ImGui::GetFontSize() * name.size() / 2;
                ImGui::SameLine(ImGui::GetWindowSize().x / 2 - font_size + (font_size / 2));
                ImGui::Text(name.c_str());

                ImGui::NewLine();
                ImGui::Separator();
                ImGui::NewLine();
               
                // Get Parent Name // 
                ImGui::Text("Parent Object : %s", m_selectEntity->GetParent()->GetName().c_str());
                ImGui::NewLine();
                ImGui::Separator();
                ImGui::NewLine();


                // Text Components //
                std::string components = "Components";
                float font_size1 = ImGui::GetFontSize() * components.size() / 2;
                ImGui::NewLine();
                ImGui::SameLine(ImGui::GetWindowSize().x / 2 - font_size1 + (font_size1 / 2));
                ImGui::Text(components.c_str());
                ImGui::NewLine();
                
                // Get Transform //               
                ImGui::SeparatorText("Transform");
                ImGui::NewLine();
                ImGui::Text("Position (X/Y)");
                if (ImGui::InputFloat2("  ", &tr->position.x))
                {
                    
                }

                // Get Rotation //
                ImGui::Text("Rotation");
                if (ImGui::InputFloat(" ", &tr->rotation))
                {

                }
                // Get Scale //                
                ImGui::Text("Scale (X/Y)");
                if (ImGui::InputFloat2(" ", &tr->scale.x))
                {

                }
                ImGui::NewLine();

                // Get ImagePath //

                if (sr != nullptr)
                {
                    ImGui::SeparatorText("Sprite Renderer");
                    ImGui::NewLine();
                    ImGui::Text("Path Image :");
                    ImGui::Text("%sr", sr->GetTexture().c_str());
                    ImGui::NewLine();
                }

                // Get Collider //
                if (bc != nullptr)
                {
                    ImGui::SeparatorText("Box Collider");
                    ImGui::NewLine();
                    if (&tr->isMovingEntity)
                    {
                        ImGui::Text("IsMovingEntity : true");
                    }
                    else
                    { 
                        ImGui::Text("IsMovingEntity : false"); 
                    }

                    // Get Static //
                    bool a = bc->GetIsStatic();
                    if (a)
                    {
                        ImGui::Text("IsStatic");
                    }
                    if (ImGui::Checkbox("IsStatic", &a))
                    {
                        a = true;
                    }
                }
                ImGui::End();
            }
        }

    }
#if defined _DEBUG || _QA
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
        if (m_instance)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }  
#endif

    void Editor::DrawFps()
    {
        ImGui::SetNextWindowSize(ImVec2(125, 70));

        if (ImGui::Begin("FPS", NULL, ImGuiWindowFlags_NoCollapse))

        {
            std::string FpsString = std::format(" {:.0f}", m_fps);
            ImGui::Text(" %s", FpsString.c_str());

        }
        ImGui::End();
    }
}