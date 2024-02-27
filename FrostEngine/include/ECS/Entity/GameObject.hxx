#include "GameObject.h"
#pragma once

namespace frost::ECS
{
    template<typename Component>
    inline Component* GameObject::GetComponent() const
    {
        static_assert(std::is_base_of<IComponent, Component>());

        for (auto& component : m_components)
        {
            if (component->GetTypeName() == Component::GetStaticTypeName())
            {
                return dynamic_cast<Component*>(component);
            }
        }

        return nullptr;
    }

    template<typename Component>
    inline void GameObject::RemoveComponent()
    {
        static_assert(std::is_base_of<IComponent, Component>());
        static_assert(!std::is_same_v<frost::ECS::Transform, Component>, "'Transform' component cannot be removed from a GameObject");

        for (auto& component : m_components)
        {
            if (component->GetTypeName() == Component::GetStaticTypeName())
            {
				m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end());
				delete component;
				break;
			}
		}
    }

    template<typename Component>
    inline Component* GameObject::AddComponent()
    {
        static_assert(std::is_base_of<IComponent, Component>());

        if (GetComponent<Component>())
        {
            return nullptr;
        }

        Component* component = new Component(*this);
        m_components.push_back(component);
        return component;
    }
}