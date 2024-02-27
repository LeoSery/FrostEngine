#include "ECS/Component/Components/Transform.h"
#include "Core/SceneManagement/SceneManager.h"
#include "ECS/Component/IComponent.h"
#include "ECS/Entity/GameObject.h"
#include "Utils/Logger.h"

#include <iostream>

namespace frost::ECS
{
    GameObject::GameObject(std::string _Name, GameObject* _Parent)
        : Tree<GameObject>(_Parent), m_name(std::move(_Name)), m_uuid(uuids::uuid_system_generator{}())
    {
        AddComponent<Transform>();
        SetActive(true);
        Start();
    }

    GameObject::GameObject(std::string _Name)
        : GameObject(std::move(_Name), core::SceneManager::GetInstance().GetActiveScene().GetRoot())
    {

    }

    GameObject::~GameObject()
    {
        //Destroy();
        for (const IComponent* component : m_components)
        {
            delete component;
        }

        m_components.clear();
    }

    void GameObject::Start()
    {
        for (IComponent* component : m_components)
        {
            component->Start();
        }
    }

    void GameObject::Update(float _DeltaTime)
    {
        for (IComponent* component : m_components)
        {
            component->Update(_DeltaTime);
        }
    }

    void GameObject::Destroy()
    {
        for (IComponent* component : m_components)
        {
            component->Destroy();
        }
    }

    const std::string& GameObject::GetName() const
    {
        return m_name;
    }

    void GameObject::SetName(const std::string& _Name)
    {
        m_name = _Name;
    }

    const Transform& GameObject::GetTransform() const
    { 
        return *GetComponent<Transform>();
    }

    void GameObject::SetTransform(const Transform& _Transform)
    {
        Transform& transformComponent = *GetComponent<Transform>();

        transformComponent.position = _Transform.position;
        transformComponent.rotation = _Transform.rotation;
        transformComponent.scale = _Transform.scale;
    }

    void GameObject::AddTag(const std::string& _Tag)
    {
        m_tags.insert(_Tag);
    }

    bool GameObject::HasTag(const std::string& _Tag) const
    { 
        return m_tags.find(_Tag) != m_tags.end();
    }

    void GameObject::RemoveTag(const std::string& _Tag)
    {
        m_tags.erase(_Tag);
    }

    bool GameObject::IsActive() const 
    {
        return m_isActive;
    }

    void GameObject::SetActive(bool _IsActive)
    {
        m_isActive = _IsActive;
    }

    uuids::uuid GameObject::GetUUID() const
    {
        return m_uuid;
    }

    void GameObject::GetData(bool _ForceLoggerDraw) const
    {
        frost::utils::Logger* Logger = frost::utils::Logger::GetInstance();

        Logger->LogInfo(m_name + " Infos: ");
        Logger->LogInfo("- Parent: " + GetParent()->GetName());
        Logger->LogInfo(std::format("- UUID: {}", uuids::to_string(m_uuid)));

        Logger->LogInfo("- Name: " + m_name);

        GetTransform().GetData(false);

        std::string tags;
        tags += "- Tags: {";
        if (m_tags.empty())
        {
            tags += " None";
        }
        else
        {
            for (const auto& tag : m_tags)
            {
                tags += " " + tag + ",";
            }
            tags += " }";
        }
        Logger->LogInfo(tags);

        std::string status = m_isActive ? "True" : "False";
        Logger->LogInfo("- Active: " + status);

        if (_ForceLoggerDraw)
            Logger->Show();
    }
}