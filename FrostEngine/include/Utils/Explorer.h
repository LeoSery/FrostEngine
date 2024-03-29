#pragma once

#include "Core/Internal/Export.h"

#include "cstdint"
#include "string_view"
#include "filesystem"
#include "string"

namespace frost::utils
{
	
	namespace fs = std::filesystem;
	class FROST_ENGINE_API Explorer 
	{
	public:

		//Constructors and Destructors
		//Explorer();
		Explorer();
		~Explorer();

		
		//Methods
		void DrawExplorer();
		void DrawMenu();
		void DrawContent();
		void DrawActions();
		void DrawFilter();



		// Singleton
		//[[nodiscard]] static Explorer*  GetInstance();
		//static void DeleteInstance();
		fs::path CurrentPath;
	private:

		//static Explorer* m_Instance;



	};

}

