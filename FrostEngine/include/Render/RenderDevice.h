#pragma once

#include "Core/Export.h"
#include <memory>
#include "Render\Shader.h"

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


	private:
		unsigned int vao;
		unsigned int vs;
		unsigned int fs;
	

		int          positionLocation;
		int          rotationLocation;
		int          scaleLocation;
		int          aspectRatioLocation;

		Shader shaderProgram;


	//forward Declaraction for pimple idiom
	private:
		struct Internal;
		std::unique_ptr<Internal> m_internal;
	};

}

