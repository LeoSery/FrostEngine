#pragma once

#include "ECS/Component/IComponent.h"
#include "glm/vec4.hpp"

namespace frost::ECS
{
	class GameObject;
	class Transform;

	enum class S_SpriteType
	{
		none,
		square,
		triangle,
		circle
	};

	class SpriteRenderer : public IComponent
	{
		FROST_DEFINE_RTTI(SpriteRenderer)

	public:

		// Constructors and Destructors
		SpriteRenderer(GameObject& _GameObject, S_SpriteType& _SpriteType);
		SpriteRenderer(GameObject& _GameObject, S_SpriteType& _SpriteType, const glm::vec4& _NewColor);
		SpriteRenderer(GameObject& _GameObject, S_SpriteType& _SpriteType, const std::string& _SpriteTexturePath);
		SpriteRenderer(GameObject& _GameObject, S_SpriteType& _SpriteType, const std::string& _SpriteTexturePath, const glm::vec4& _Color);

		~SpriteRenderer();

		// Frost engine life cycle methods
		virtual void Start() override;
		virtual void Update(float _DeltaTime) override;
		virtual void Destroy() override;

		// Getters and Setters
		[[nodiscard]] virtual void GetData(bool _ForceLoggerDraw) const;

		[[nodiscard]] S_SpriteType GetSpriteType() const;
		void SetSpriteType(S_SpriteType _NewSpriteType);

		[[nodiscard]] std::string GetTexture() const;
		void SetTexture(const std::string& _NewTexutePath);

		[[nodiscard]] glm::vec4 GetColor() const;
		void SetColor(const glm::vec4& _NewColor);

	private:
		S_SpriteType m_spriteType = S_SpriteType::none;
		std::string m_spriteTexturePath = "";
		glm::vec4 m_color = { 1, 1, 1, 1 };
	};
}