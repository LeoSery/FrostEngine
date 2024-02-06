#include "ECS/GameObject.h"

#include <iostream>

namespace frost::ECS
{
    GameObject::GameObject(std::string _Name, GameObject* _Parent, frost::core::Transform _Transform)
        : Tree<GameObject>(_Parent), m_Name(_Name), m_Transform(_Transform) 
    {
        SetActive(true);
    }

    const std::string& GameObject::GetName() const
    {
        return m_Name;
    }

    void GameObject::SetName(const std::string& _Name)
    {
        m_Name = _Name;
    }

    const frost::core::Transform& GameObject::GetTransform() const
    { 
        return m_Transform;
    }

    void GameObject::SetTransform(const frost::core::Transform& _Transform)
    {
        m_Transform = _Transform;
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

    void GameObject::GetData(std::ostream& _Stream) const
    {
        _Stream << "GameObject Infos:" << std::endl;
        _Stream << "  - Name: " << m_Name << std::endl;
        _Stream << "  - Transform: ";
        m_Transform.GetData(_Stream);
        _Stream << "  - Tags:";
        if (m_Tags.empty())
        {
            _Stream << " None" << std::endl;
        }
        else
        {
            for (const auto& tag : m_Tags)
            {
                _Stream << " " << tag << ",";
            }
            _Stream << std::endl;
        }
        _Stream << "  - Active: " << m_isActive << std::endl;
    }
}