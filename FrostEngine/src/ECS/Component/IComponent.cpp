#include "ECS/Component/IComponent.h"
#include "ECS/Entity/GameObject.h"

namespace frost::ECS
{
	IComponent::IComponent(GameObject& _GameObject) : m_parentObject(_GameObject), m_uuid(uuids::uuid_system_generator{}())
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
		return m_uuid;
	}

	GameObject& IComponent::GetParentObject() const
	{
		return m_parentObject;
	}
}