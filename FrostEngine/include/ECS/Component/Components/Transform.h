#pragma once

#include "ECS/Component/IComponent.h"
#include "glm/vec2.hpp"

namespace frost::ECS
{
	class GameObject;

	class Transform : public IComponent
	{
		FROST_DEFINE_RTTI(Transform)

	public:

		// Constructors and Destructors
		Transform(GameObject& _GameObject);
		~Transform();

		// Frost engine life cycle methods
		virtual void Start() override;
		virtual void Update(float fDeltaTime) override;
		virtual void Destroy() override;

		// Getters and Setters
		void GetData(bool _ShowImmediately) const;

		// Component methods
		void Translate(const glm::vec2& _Translation);
		void Rotate(float _Rotation);
		void Scale(const glm::vec2& _Scale);

		//fields
		glm::vec2 position = {0, 0};
		float rotation = 0;
		glm::vec2 scale = { 1, 1 };
	};
}
