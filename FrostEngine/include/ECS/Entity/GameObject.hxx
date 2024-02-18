#pragma once

namespace frost::ECS
{
    template<typename Component>
    inline Component* GameObject::GetComponent() const
    {
        static_assert(std::is_base_of<IComponent, Component>());

        for (auto& component : m_Components)
        {
            if (component->GetTypeName() == Component::GetStaticTypeName())
            {
                return dynamic_cast<Component*>(component);
            }
        }

        return nullptr;
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
        m_Components.push_back(component);
        return component;
    }
}