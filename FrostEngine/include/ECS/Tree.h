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
		T* GetParent();
		T* GetRoot();

		void RemoveChild(T* _TargetChild);
		void AddChild(T* _TargetChild);

		size_t const m_UUID;
	private:
		void SetParent(T* _TargetParent);
		T* m_CurrentParent = nullptr;
		std::vector<T*> m_Children;
	};

    template<typename T>
    Tree<T>::Tree(T* _Parent) : m_UUID(m_Children.size() + 1)
    {
        SetParent(_Parent);
    }

    template<typename T>
    Tree<T>::~Tree()
    {
        if (m_CurrentParent)
            m_CurrentParent->RemoveChild(static_cast<T*>(this));

        for (auto* child : m_Children)
        {
            delete child;
        }
    }

    template<typename T>
    std::vector<T*> Tree<T>::GetChildren()
    {
        return m_Children;
    }

    template<typename T>
    T* Tree<T>::GetParent()
    {
        return m_CurrentParent;
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
        auto iterator = std::find(m_Children.begin(), m_Children.end(), _TargetChild);

        if (iterator != m_Children.end())
        {
            m_Children.erase(iterator);
        }
    }

    template<typename T>
    void Tree<T>::AddChild(T* _TargetChild)
    {
        auto iterator = std::find(m_Children.begin(), m_Children.end(), _TargetChild);

        if (iterator == m_Children.end())
        {
            m_Children.push_back(_TargetChild);
        }
    }

    template<typename T>
    void Tree<T>::SetParent(T* _TargetParent)
    {
        if (m_CurrentParent != nullptr)
        {
            m_CurrentParent->RemoveChild(static_cast<T*>(this));
        }

        m_CurrentParent = _TargetParent;

        if (m_CurrentParent != nullptr)
        {
            m_CurrentParent->AddChild(static_cast<T*>(this));
        }
    }
}
