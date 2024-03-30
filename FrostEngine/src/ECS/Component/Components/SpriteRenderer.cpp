#include "ECS/Component/Components/SpriteRenderer.h"
#include "ECS/Entity/GameObject.h"
#include <Render/RenderDevice.h>
#include "Render/Texture.h"
#include "Utils/Logger.h"
#include<array> 


namespace frost::ECS
{
	float squareVertices[16] =
	{
	-1.0f,  1.0f, /*UV*/0.0f, 1.0f,
	-1.0f, -1.0f, /*UV*/0.0f, 0.0f,
	 1.0f, -1.0f, /*UV*/1.0f, 0.0f,
	 1.0f,  1.0f, /*UV*/1.0f, 1.0f,
	};

	unsigned int squareIndices[6] = { 0, 1, 2, 0, 2, 3 };

	SpriteRenderer::SpriteRenderer(GameObject& _GameObject) : IComponent(_GameObject)
	{
		vertices = new float[16];
		std::copy(squareVertices, squareVertices + 16, vertices);

		indices = new unsigned int[6];
		std::copy(squareIndices, squareIndices + 6, indices);

		VBO.CreateData(vertices, sizeof(float) * 16);

		IBO.CreateData(indices, sizeof(unsigned int) * 6);

		VAO.BindBuffer(frost::render::VertexArrayObject::E_TypeBuffer::VBO, VBO);
		VAO.BindBuffer(frost::render::VertexArrayObject::E_TypeBuffer::IBO, IBO);

		m_spriteTexture = new frost::render::Texture();

		VAO.SetTexture(m_spriteTexture);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		delete[] vertices;
		delete[] indices;
		delete m_spriteTexture;
		frost::utils::Logger::GetInstance()->LogInfo("SpriteRenderer destroyed.");
	}

	void SpriteRenderer::Start()
	{
		frost::render::RenderDevice::GetInstance()->AddVAO(VAO);
	}

	void SpriteRenderer::Update(float /*_DeltaTime*/)
	{
		VAO.SetLocation({ this->GetParentObject().GetComponent<Transform>()->position });
		VAO.SetScale({ this->GetParentObject().GetComponent<Transform>()->scale });
		VAO.SetRotation({ this->GetParentObject().GetComponent<Transform>()->rotation });
		frost::render::RenderDevice::GetInstance()->AddVAO(VAO);
	}

	void SpriteRenderer::GetData(bool _ForceLoggerDraw) const
	{
		frost::utils::Logger* Logger = frost::utils::Logger::GetInstance();

		std::string PathString = "{ Path: " + m_spriteTexturePath + ";";
		std::string ColorString = " Color: [r: " + std::to_string(m_color.r) + " g: " + std::to_string(m_color.g) + " b: " + std::to_string(m_color.b) + " a: " + std::to_string(m_color.a) + "]; }";

		Logger->LogInfo("- SpriteRenderer: " + PathString + ColorString);

		if (_ForceLoggerDraw)
			Logger->Show();
	}

	std::string SpriteRenderer::GetTexture() const
	{
		return m_spriteTexturePath;
	}

	void SpriteRenderer::SetTexture(const std::string& _NewTexturePath)
	{
		m_spriteTexturePath = _NewTexturePath;
		m_spriteTexture->SetTexture(m_spriteTexturePath);
	}

	glm::vec4 SpriteRenderer::GetColor() const
	{
		return m_color;
	}

	void SpriteRenderer::SetColor(const glm::vec4& _Color)
	{
		m_color = _Color;
	}
}
