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
        //frost::utils::Explorer* m_Explorer{};
        m_SceneManager = &frost::core::SceneManager::GetInstance();
        m_CurrentScene = &m_SceneManager->GetActiveScene();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(300, 700));
        if (ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoCollapse))

        {
            DrawHierachyValue(m_CurrentScene);
            DrawInsperctorValue();
            ImGui::End();
        }

        ImGui::SetNextWindowSize(ImVec2(300, 705));
        ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse);
        ImGui::End();
            

#ifdef _DEBUG
        ImGui::SetNextWindowSize(ImVec2(700, 200));
        if (ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoCollapse))
        {
             frost::utils::Logger::GetInstance()->DrawLogger();
            ImGui::End();
        }
        
        ImGui::SetNextWindowSize(ImVec2(900, 200));
        if (ImGui::Begin("Explorer", NULL, ImGuiWindowFlags_NoCollapse))
        {
            if (ImGui::Button("Go Up"))
            {
                if (CurrentPath.has_parent_path())
                {
                    CurrentPath = CurrentPath.parent_path();
                }
            }
            ImGui::SameLine();
            ImGui::Text("Currenty directoy : %s", CurrentPath.string().c_str());
            ImGui::Separator();
            DrawExplorerContent();
            ImGui::Separator();
            DrawExplorerActions();
            ImGui::Separator();
            DrawExplorerFilter();


            ImGui::End();
        }
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

    void Editor::DrawInsperctorValue()
    {
        if (SelectEntity != nullptr)
        {
            if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse))
            {
                //ImGui::GetMainViewport();
                frost::ECS::Transform* tr = SelectEntity->GetComponent<frost::ECS::Transform>();
                frost::ECS::SpriteRenderer* sr = SelectEntity->GetComponent<frost::ECS::SpriteRenderer>();
                //frost::core::RenderDevice* rd = frost::core::RenderDevice::GetInstance();
                frost::ECS::BoxCollider* bc = SelectEntity->GetComponent<frost::ECS::BoxCollider>();

                // Get Transform //
                //ImGui::InputFloat2("Transform[X/Y]", &tr->position.x);
                if (ImGui::InputFloat2("Transform[X/Y]", &tr->position.x))
                {
                    //ISOnInspector = false;
                }
                // Get Rotation //
                //ImGui::InputFloat("Rotation", &tr->rotation);
                if (ImGui::InputFloat2("Rotation", &tr->rotation))
                {

                }
                // Get Scale //
                //ImGui::InputFloat2("Scale[X/Y]", &tr->scale.x);
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

                ImGui::Text("Path Image : %sr" , sr->GetTexture().c_str());
                bool a = bc->GetIsStatic();
                if (ImGui::Checkbox("IsStatic", &a))
                {
                    /*tr->isMovingEntity = true;
                    if (!tr->isMovingEntity)
                    {
                        tr->isMovingEntity = false;
                    }*/

                }
                //ImGui::Checkbox("Box Collider", &bc->);

                //ImGui::Button(sr->GetColor().c_str());
                //auto aa = sr->GetColor().x;
                //float ColorA[] = { rd->GetClearColor().x,rd->GetClearColor().y,rd->GetClearColor().z,rd->GetClearColor().w };
                //ImGui::ColorEdit4("Color Edit ",ColorA);

                //SpriteRenderer* sr = m_child->GetComponent<SpriteRenderer>();
                ImGui::End();
            }
        }

    }

    void Editor::DrawExplorerContent()
    {
        for (const auto &entry : fs::directory_iterator(CurrentPath))
        {
            const auto is_selected = entry.path() == selectedEntry;
            const auto is_directory = entry.is_directory();
            const auto is_file = entry.is_regular_file();
            auto entry_name = entry.path().filename().string();

            if (is_directory)         
                entry_name = "[Directory]" + entry_name;
            else if (is_file)
                entry_name = "[File]" + entry_name;
            
            if (ImGui::Selectable(entry_name.c_str(), is_selected))
            {
                if (is_directory)
                    CurrentPath /= entry.path().filename();

                selectedEntry = entry.path();
            }
        }
    }

    void Editor::DrawExplorerFilter()
    {
        static char extension_filter[16] = { "\0" };

        ImGui::Text("Filter by extension");
        ImGui::SameLine();
        ImGui::InputText("###inFilter", extension_filter, sizeof(extension_filter));

        if (std::strlen(extension_filter) == 0)
            return;

        auto filtered_file_count = std::size_t{ 0 };
        for (const auto& entry : fs::directory_iterator(CurrentPath))
        {
            if (!fs::is_regular_file(entry))
                continue;

            if (entry.path().extension().string() == extension_filter)
                ++filtered_file_count;
        }

        ImGui::Text("Number of files: %u", filtered_file_count);
    }

    void Editor::DrawExplorerActions()
    {
        if (fs::is_directory(selectedEntry))
        {
            ImGui::Text("Selected dir: %s", selectedEntry.string().c_str());
        }

        else if (fs::is_regular_file(selectedEntry))
        {
            ImGui::Text("Selected file: %s", selectedEntry.string().c_str());
        }

        else
        {
            ImGui::Text("Nothing selected!");
        }

        if (fs::is_regular_file(selectedEntry) && ImGui::Button("Open"))
        {
            DrawExplorerOpenFile();
        }
        ImGui::SameLine();

        if (ImGui::Button("Rename"))
        {
            RenameDialogOpened = true;
            ImGui::OpenPopup("Rename File");
        }
        ImGui::SameLine();

        if (ImGui::Button("Delete"))
        {
            DeleteDialogOpened = true;
            ImGui::OpenPopup("Delete File");
        }

        DrawExplorerRenameFilePopUp();
        DrawExplorerDeleteFilePopUp();
    }

    void Editor::DrawExplorerRenameFilePopUp()
    {
        if (ImGui::BeginPopupModal("Rename File", &RenameDialogOpened))
        {
            static char buffer_name[512] = { '\0' };

            ImGui::Text("New name : ");
            ImGui::InputText("###newName", buffer_name, sizeof(buffer_name));

            if (ImGui::Button("Rename"))
            {
                auto new_path = selectedEntry.parent_path() / buffer_name;
                if (ExplorerRenameFile(selectedEntry, new_path))
                {
                    RenameDialogOpened = false;
                    selectedEntry = new_path;
                    std::memset(buffer_name, 0, sizeof(buffer_name));
                }
            }
            ImGui::SameLine();

            if (ImGui::Button("Cancel"))
            {
                RenameDialogOpened = false;
            }
            ImGui::EndPopup();
        }
    }

    void Editor::DrawExplorerDeleteFilePopUp()
    {
        if (ImGui::BeginPopupModal("Delete File", &DeleteDialogOpened))
        {
            ImGui::Text("Are you sure you want to delete %s ?", selectedEntry.filename().string().c_str());
            
            if (ImGui::Button("Yes"))
            {
                if (ExplorerDeleteFile(selectedEntry))
                {
                    selectedEntry.clear();
                    DeleteDialogOpened = false;
                }
            }
            ImGui::SameLine();
            
            if (ImGui::Button("No"))
            {
                DeleteDialogOpened = false;
            }
            ImGui::EndPopup();
        }
    }

    void Editor::DrawExplorerOpenFile()
    {
#ifdef _WIN32
        const auto command = "start \"\" \"" + selectedEntry.string() + "\"";

#elif _APPLE_
        const auto command = "open \"" + selectedEntry.string() + "\"";

#else
        const auto command = "xdg-open \"" + selectedEntry.string() + "\"";

#endif    
        std::system(command.c_str());
    }

    bool Editor::ExplorerRenameFile(const fs::path &old_path, const fs::path &new_path)
    {
        try
        {
            fs::rename(old_path, new_path);
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        
    }

    bool Editor::ExplorerDeleteFile(const fs::path &_path)
    {
        try
        {
            fs::remove(_path);
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
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
}