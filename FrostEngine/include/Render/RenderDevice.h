#pragma once

#include "Render/VertexArrayObject.h"
#include "Render/Texture.h"
#include "Render/Shader.h"
#include "Core/Export.h"

#include <memory>
#include <vector>

namespace frost::core 
{
	class Window;
	
	class FROST_ENGINE_API RenderDevice
	{
	public:

		// Constructors and Destructors
		RenderDevice(const RenderDevice&) = delete;
		explicit RenderDevice(Window& _Window);
		~RenderDevice();

		// Methods
		void RenderTest();
		void AddVAO(VertexArrayObject _NewVAO);

		// Frost engine life cycle methods
		void Update();

	private:

		// Fields
		unsigned int m_vao;
		unsigned int m_vs;
		unsigned int m_fs;
	
		int m_positionLocation;
		int m_rotationLocation;
		int m_scaleLocation;
		int m_aspectRatioLocation;
		int m_texture;

		float m_a = 0.0f;
		Shader m_shaderProgram;
		Texture m_testTex;
		[[nodiscard]] std::vector<VertexArrayObject> GetVaoToRender();

		// Methods
		void ClearVaosToRender();

	//forward Declaraction for pimple idiom
	private:
		struct Internal;
		std::unique_ptr<Internal> m_internal;
	};
}
