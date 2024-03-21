#pragma once

#include "ECS/Component/IComponent.h"
#include "glm/vec2.hpp"

namespace frost::ECS
{
	class GameObject;

	class FROST_ENGINE_API Transform : public IComponent
	{
		FROST_DEFINE_RTTI(Transform)

	public:

		// Constructors and Destructors
		Transform(GameObject& _GameObject);
		~Transform();

		// Frost engine life cycle methods
		virtual void Start() override;
		virtual void Update(float _DeltaTime) override;
		virtual void Destroy() override;

		// Getters and Setters
		void GetData(bool _ForceLoggerDraw) const;

		// Component methods
		void Translate(const glm::vec2& _Translation);
		void Rotate(float _Rotation);
		void Scale(const glm::vec2& _Scale);

		// Fields
		glm::vec2 position = { 0, 0 };
		float rotation = 0;
		glm::vec2 scale = { 1, 1 };
	};
}