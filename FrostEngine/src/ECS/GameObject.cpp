#include "ECS/Component/Components/Transform.h"
#include "Core/SceneManagement/SceneManager.h"
#include "ECS/Component/IComponent.h"
#include "ECS/Entity/GameObject.h"
#include "Utils/Logger.h"

#include <iostream>

namespace frost::ECS
{
    GameObject::GameObject(std::string _Name, GameObject* _Parent)
        : Tree<GameObject>(_Parent), m_Name(std::move(_Name)), m_UUID(uuids::uuid_system_generator{}())
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
        for (const IComponent* component : m_Components)
        {
            delete component;
        }

        m_Components.clear();
    }

    void GameObject::Start()
    {
        for (IComponent* component : m_Components)
        {
            component->Start();
        }
    }

    void GameObject::Update(float fDeltaTime)
    {
        for (IComponent* component : m_Components)
        {
            component->Update(fDeltaTime);
        }
    }

    void GameObject::Destroy()
    {
        for (IComponent* component : m_Components)
        {
            component->Destroy();
        }
    }

    const std::string& GameObject::GetName() const
    {
        return m_Name;
    }

    void GameObject::SetName(const std::string& _Name)
    {
        m_Name = _Name;
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
        m_Tags.insert(_Tag);
    }

    bool GameObject::HasTag(const std::string& _Tag) const
    { 
        return m_Tags.find(_Tag) != m_Tags.end();
    }

    void GameObject::RemoveTag(const std::string& _Tag)
    {
        m_Tags.erase(_Tag);
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
        return m_UUID;
    }

    void GameObject::GetData(bool _ShowImmediately) const
    {
        frost::utils::Logger* Logger = frost::utils::Logger::GetInstance();

        Logger->LogInfo(m_Name + " Infos: ");
        Logger->LogInfo("- Parent: " + GetParent()->GetName());
        //frost::utils::Logger::LogInfo("  - UUID: " + m_UUID);

        Logger->LogInfo("- Name: " + m_Name);

        GetTransform().GetData(false);

        std::string tags;
        tags += "- Tags: {";
        if (m_Tags.empty())
        {
            tags += " None";
        }
        else
        {
            for (const auto& tag : m_Tags)
            {
                tags += " " + tag + ",";
            }
            tags += " }";
        }
        Logger->LogInfo(tags);

        std::string status = m_isActive ? "True" : "False";
        Logger->LogInfo("- Active: " + status);

        if (_ShowImmediately)
            Logger->Show();
    }
}