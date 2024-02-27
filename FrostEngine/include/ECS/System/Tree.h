#pragma once

#include <vector>

namespace frost::ECS
{
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

    template<typename T>
    Tree<T>::Tree(T* _Parent)
    {
        SetParent(_Parent);
    }

    template<typename T>
    Tree<T>::~Tree()
    {
        if (m_currentParent)
            m_currentParent->RemoveChild(static_cast<T*>(this));

        for (auto* child : m_childrens)
        {
            delete child;
        }
    }

    template<typename T>
    std::vector<T*> Tree<T>::GetChildren()
    {
        return m_childrens;
    }

    template<typename T>
    T* Tree<T>::GetParent()
    {
        return m_currentParent;
    }

    template<typename T>
    const T* Tree<T>::GetParent() const
    {
        return m_currentParent;
    }

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

    template<typename T>
    void Tree<T>::RemoveChild(T* _TargetChild)
    {
        auto iterator = std::find(m_childrens.begin(), m_childrens.end(), _TargetChild);

        if (iterator != m_childrens.end())
        {
            m_childrens.erase(iterator);
        }
    }

    template<typename T>
    void Tree<T>::AddChild(T* _TargetChild)
    {
        auto iterator = std::find(m_childrens.begin(), m_childrens.end(), _TargetChild);

        if (iterator == m_childrens.end())
        {
            m_childrens.push_back(_TargetChild);
        }
    }

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
