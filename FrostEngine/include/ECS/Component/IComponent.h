#pragma once

#include "ECS/Entity/GameObject.h"

namespace frost::ECS
{
	class IComponent
	{
	public:
		IComponent() = delete;
		IComponent(GameObject& _GameObject);

		virtual ~IComponent();

		virtual void Start() = 0;
		virtual void Update(float _DeltaTime) = 0;
		virtual void Destroy() = 0;

		[[nodiscard]] virtual const std::string GetComponentName() const = 0;

		[[nodiscard]] bool IsActive() const;
		void SetActive(bool _IsActive);

		[[nodiscard]] uuids::uuid GetUUID() const;

	protected:
		GameObject& GetParentObject() const;

	private:
		uuids::uuid m_UUID;
		GameObject& ParentObject;
		bool m_isActive = true;
	};
}
