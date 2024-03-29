#pragma once

/*!
* \file Tree.h
* 
* \brief Header file for the Tree class.
*/

#include <vector>

/*!
* \namespace frost::ECS
*
* \brief The namespace for FrostEngine's Entity Component System.
*/
namespace frost::ECS
{
    /*!
    * \class Tree
	*
	* \brief The 'Tree' class is the system behind everything in FrostEngine.
    * It allows you to parent any class passed as a parameter. It is notably
    * used for GameObjects.
	*
	* \tparam <T> The type of the tree.
	*/
	template<typename T>
	class Tree
	{
	public:
		explicit Tree(T* _Parent = nullptr);
		virtual ~Tree();

		std::vector<T*> GetChildren();
		void SetParent(T* _TargetParent);
		T* GetParent();
        const T* GetParent() const;
		T* GetRoot();

		void RemoveChild(T* _TargetChild);
		void AddChild(T* _TargetChild);

	private:
		T* m_currentParent = nullptr;
		std::vector<T*> m_childrens;
	};

    /*!
    * \brief The constructor of the Tree class.
    *
    * \fn Tree(T* _Parent)
    *
    * \tparam <T> The type of the tree.
    */
    template<typename T>
    Tree<T>::Tree(T* _Parent)
    {
        SetParent(_Parent);
    }

    /*!
    * \brief The destructor of the Tree class.
    * 
    * \details It deletes all the childrens of the current <T> entity that composes the Tree.
    * 
    * \fn ~Tree()
    */
    template<typename T>
    Tree<T>::~Tree()
    {
        if (m_currentParent)
            m_currentParent->RemoveChild(static_cast<T*>(this));

        std::vector<T*> TempChildrens = m_childrens;

        for (auto* child : TempChildrens)
        {
            delete child;
        }

        m_childrens.clear();
    }

    /*!
    * \brief Retrieves all the childs of the current <T> entity that composes the Tree.
    * 
    * \details Returns all the childrens stored in the m_childrens vector for the current <T> entity.
    * 
    * \fn GetChildren()
    * 
    * \tparam <T> The type of the tree.
    * 
    * \return A vector of pointers to the childrens of the current <T> entity.
    */
    template<typename T>
    std::vector<T*> Tree<T>::GetChildren()
    {
        return m_childrens;
    }

    /*!
    * \brief Retrieves the parent of the current <T> entity that composes the Tree.
    * 
    * \fn GetParent()
    * 
    * \tparam <T> The type of the tree.
    * 
    * \return A pointer to the parent of the current <T> entity.
    */
    template<typename T>
    T* Tree<T>::GetParent()
    {
        return m_currentParent;
    }

    /*!
    * \brief Retrieves the parent of the current <T> entity that composes the Tree (const).
    * 
    * \fn GetParent()
    * 
    * \tparam <T> The type of the tree.
    * 
    * \return A pointer to the parent of the current <T> entity.
    */
    template<typename T>
    const T* Tree<T>::GetParent() const
    {
        return m_currentParent;
    }

    /*!
    * \brief Retrieves the root of the current <T> entity that composes the Tree.
    * 
    * \details Returns the root of the current <T> entity by going through all the parents until it reaches the root.
    * 
    * \fn GetRoot()
    * 
    * \tparam <T> The type of the tree.
    * 
    * \return A pointer to the root of the current <T> entity.
    */
    template<typename T>
    T* Tree<T>::GetRoot()
    {
        T* CurrentObject = static_cast<T*>(this);

        while (CurrentObject->GetParent() != nullptr)
        {
            CurrentObject = CurrentObject->GetParent();
        }
        return CurrentObject;
    }

    /*!
    * \brief Removes a child from the current <T> entity that composes the Tree.
    * 
    * \details Removes a child from the m_childrens vector of the current <T> entity.
    * 
    * \fn RemoveChild(T* _TargetChild)
    * 
    * \tparam <T> The type of the tree.
    * 
    * \param _TargetChild The child to remove from the current <T> entity.
    */
    template<typename T>
    void Tree<T>::RemoveChild(T* _TargetChild)
    {
        auto iterator = std::find(m_childrens.begin(), m_childrens.end(), _TargetChild);

        if (iterator != m_childrens.end())
        {
            m_childrens.erase(iterator);
        }
    }

    /*!
    * \brief Adds a child to the current <T> entity that composes the Tree.
    * 
    * \details Adds a child to the m_childrens vector of the current <T> entity.
    * 
    * \fn AddChild(T* _TargetChild)
    * 
    * \tparam <T> The type of the tree.
    * 
    * \param _TargetChild The child to add to the current <T> entity.
    */
    template<typename T>
    void Tree<T>::AddChild(T* _TargetChild)
    {
        auto iterator = std::find(m_childrens.begin(), m_childrens.end(), _TargetChild);

        if (iterator == m_childrens.end())
        {
            m_childrens.push_back(_TargetChild);
        }
    }

    /*!
    * \brief Sets the parent of the current <T> entity that composes the Tree.
    * 
    * \details Sets the parent of the current <T> entity and updates the parent's childrens vector.
    * 
    * \fn SetParent(T* _TargetParent)
    * 
    * \tparam <T> The type of the tree.
    */
    template<typename T>
    void Tree<T>::SetParent(T* _TargetParent)
    {
        if (m_currentParent != nullptr)
        {
            m_currentParent->RemoveChild(static_cast<T*>(this));
        }

        m_currentParent = _TargetParent;

        if (m_currentParent != nullptr)
        {
            m_currentParent->AddChild(static_cast<T*>(this));
        }
    }
}
