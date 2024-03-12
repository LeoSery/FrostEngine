#pragma once
#include "Core/Export.h"
#include <string>

namespace frost::core
{
	class FROST_ENGINE_API Texture
	{
	public:

		// Constructor and Destructor
		Texture(const std::string& _Name);
		Texture();
		~Texture();

		// Fields
		bool SetTexture(const std::string _name);

		// Methods
		void Bind(unsigned int _Slot = 0) const;
		void Unbind();

		// Getters
		[[nodiscard]] inline int GetWidth() const { return Width; }
		[[nodiscard]] inline int GetHeight() const { return Height; }
		[[nodiscard]] inline unsigned int GetID() const { return ID; }


	private:
		void initialize(); //just didn't liked duplicated code
		bool LoadImage(const std::string _name);

		unsigned int ID;
		std::string FilePath;
		unsigned char* LocalBuffer;
		int Width, Height, BPP;
	};
}
