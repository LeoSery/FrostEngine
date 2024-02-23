#pragma once

#include "Core/Export.h"
#include <memory>
#include <vector>

#include "Render\Shader.h"
#include "Render/VertexArrayObject.h"

namespace frost::core 
{

	class Window;
	
	class FROST_ENGINE_API RenderDevice
	{

	public:
		RenderDevice(const RenderDevice&) = delete;
		
		explicit RenderDevice(Window& _window);
		~RenderDevice();

		void test();

		void Update();
		void AddVao(VertexArrayObject _newVao);

	private:
		unsigned int vao;
		unsigned int vs;
		unsigned int fs;
	

		int          positionLocation;
		int          rotationLocation;
		int          scaleLocation;
		int          aspectRatioLocation;

		float a = 0.0f;
		Shader shaderProgram;

	
		void ClearVaosToRender();
		std::vector<VertexArrayObject> GetVaoToRender();

	//forward Declaraction for pimple idiom
	private:
		struct Internal;
		std::unique_ptr<Internal> m_internal;
	};

}

