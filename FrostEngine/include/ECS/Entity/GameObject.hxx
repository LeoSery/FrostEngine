#pragma once

/*!
* \file GameObject.hxx
* 
* \brief Templated implementation of the 'GameObject' class.
*/

#include "GameObject.h"

namespace frost::ECS
{
    /*!
    * \brief Get a component of the specified type from the GameObject.
    * 
    * \detail This function will find the specified component in the GameObject's component list and return it.
    * 
    * \fn GameObject::GetComponent() const
    * 
    * \tparam Component The type <T> of the component to get.
    * 
    * \return The type <T> component of the specified type if it exists, otherwise nullptr.
    */
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

    /*!
    * \brief Remove a component of the specified type from the GameObject.
    * 
    * \detail This function will find the specified component in the GameObject's component list and remove it.
    * 
    * \fn GameObject::RemoveComponent()
    * 
    * \tparam Component The type <T> of the component to remove.
	*/
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

    /*!
    * \brief Add a component of the specified type to the GameObject.
    * 
    * \detail This function will add a new component of the specified type to the GameObject's component list.
    * 
    * \fn GameObject::AddComponent()
    * 
    * \tparam Component The type <T> of the component to add.
    */
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
