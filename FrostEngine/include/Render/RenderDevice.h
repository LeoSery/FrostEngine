#pragma once

/*!
* \file RenderDevice.h
*
* \brief Header file for the RenderDevice class.
*/

#include "Render/VertexArrayObject.h"
#include "Render/Texture.h"
#include "Render/Shader.h"

#include "Core/Internal/Export.h"

#include "glm/glm.hpp"

#include <memory>
#include <vector>

namespace frost::core
{
	class Window;
}

/*!
* \namespace frost::render
*
* The namespace for FrostEngine's rendering functionalities.
*/
namespace frost::render
{
	/*!
	* \class RenderDevice
	* 
	* \brief The class that manages the rendering of the FrostEngine.
	* 
	* \details Create VAO, VBO, Shader and render them.
	*/
	class FROST_ENGINE_API RenderDevice
	{
	public:

		// Constructors and Destructors
		RenderDevice(const RenderDevice&) = delete;
		explicit RenderDevice();
		~RenderDevice();

		/*!
		* \brief Init() will be executed when Application::Init() is called.
		* \details this method call glewInit(), set the shader used and get uniform locations later used in the rendering update.
		* \fn Init(const frost::core::Window* _window)
		* \param _window The window to render to.
		*/
		RenderDevice* Init(const frost::core::Window* _window);

		/*! 
		* \brief RenderDevice::GetInstance() return the instance of the RenderDevice.
		* \fn GetInstance()
		* \return RenderDevice* The instance of the RenderDevice.
		*/
		static RenderDevice* GetInstance();
		static RenderDevice* m_instance;

		/*!
		* \brief AddVAO() is called in all objects that want to send geometry to render.
		* \fn AddVAO(VertexArrayObject _NewVAO)
		* \param _NewVAO The VAO to render.
		*/
		void AddVAO(VertexArrayObject _NewVAO);
		
		/*!
		* \brief SetZoom() set the uniform zoom in the shader used to render.
		* \fn SetZoom(float _zoom)
		* \param _zoom The zoom to set.
		*/
		void SetZoom(float _zoom);
		
		/*!
		* \brief GetZoom() get the uniform zoom in the shader used to render.
		* \fn GetZoom()
		* \return zoom float.
		*/
		float GetZoom();

		/*!
		* \brief SetClearColor() set the clear color of the window.
		* \fn SetClearColor(glm::vec4 _color)
		* \param _color The color to set.
		*/
		void SetClearColor(glm::vec4 _color);

		/*!
		* \brief Update() is called in the main loop of the application.
		* it's the method that render all the VAOs.
		*/
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
		int m_zoom;

		glm::vec4 m_clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

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
