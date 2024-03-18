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
		explicit RenderDevice();
		~RenderDevice();

		RenderDevice* Init(const Window* _window);

		static RenderDevice* GetInstance();

		static RenderDevice* m_instance;


		// Methods
		void AddVAO(VertexArrayObject _NewVAO);

		// Frost engine life cycle methods
		void Update();

	private:

		// Fields
		unsigned int m_vao = 0;
		unsigned int m_vs = 0;
		unsigned int m_fs = 0;

		int m_positionLocation;
		int m_rotationLocation;
		int m_scaleLocation;
		int m_aspectRatioLocation;
		int m_texture;

		Shader m_shaderProgram;
		[[nodiscard]] std::vector<VertexArrayObject> GetVaoToRender();

		// Methods
		void ClearVaosToRender();

		//forward Declaraction for pimple idiom
	private:
		struct Internal;
		std::unique_ptr<Internal> m_internal;
	};
}
