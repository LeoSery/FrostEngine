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

		virtual const std::string GetComponentName() const = 0;

		virtual void DrawInInspector() = 0;

	protected:
		GameObject& GetEntity() const;

	private:
		GameObject& ParentGameObject;
	};
}
