#include "ECS/Component/IComponent.h"
#include "ECS/Entity/GameObject.h"

namespace frost::ECS
{
	IComponent::IComponent(GameObject& _GameObject) : ParentObject(_GameObject)
	{
		
	}

	IComponent::~IComponent()
	{

	}

	bool IComponent::IsActive() const
	{
		return m_isActive;
	}

	void IComponent::SetActive(bool _IsActive)
	{
		m_isActive = _IsActive;
	}

	uuids::uuid IComponent::GetUUID() const
	{
		return m_UUID;
	}

	GameObject& IComponent::GetParentObject() const
	{
		return ParentObject;
	}
}
