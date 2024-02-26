#pragma once

#pragma once

#include "ECS/Component/IComponent.h"
#include "glm/vec4.hpp"

namespace frost::ECS
{
	class GameObject;
	class Transform;

	enum class SpriteType
	{
		None,
		Square,
		Triangle,
		Circle
	};

	class SpriteRenderer : public IComponent
	{
		FROST_DEFINE_RTTI(SpriteRenderer)

	public:

		// Constructors and Destructors
		SpriteRenderer(GameObject& _GameObject, SpriteType& _SpriteType);
		SpriteRenderer(GameObject& _GameObject, SpriteType& _SpriteType, const glm::vec4& _NewColor);
		SpriteRenderer(GameObject& _GameObject, SpriteType& _SpriteType, const std::string& _SpriteTexturePath);
		SpriteRenderer(GameObject& _GameObject, SpriteType& _SpriteType, const std::string& _SpriteTexturePath, const glm::vec4& _Color);

		~SpriteRenderer();

		// Frost engine life cycle methods
		virtual void Start() override;
		virtual void Update(float fDeltaTime) override;
		virtual void Destroy() override;

		// Getters and Setters
		virtual void GetData(bool _ShowImmediately) const;

		SpriteType GetSpriteType() const;
		void SetSpriteType(SpriteType _NewSpriteType);

		std::string GetTexture() const;
		void SetTexture(const std::string& _NewTexutePath);

		glm::vec4 GetColor() const;
		void SetColor(const glm::vec4& _NewColor);

	private:
		SpriteType m_SpriteType = SpriteType::None;
		std::string m_spriteTexturePath = "";
		glm::vec4 m_color = { 1, 1, 1, 1 };
	};
}
