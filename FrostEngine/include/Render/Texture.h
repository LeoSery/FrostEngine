#pragma once

#include <string>

namespace frost::core
{
	class Texture
	{
	public:

		// Constructor and Destructor
		Texture(const std::string& _Name);
		~Texture();

		// Methods
		void Bind(unsigned int _Slot = 0) const;
		void Unbind();

		// Getters
		[[nodiscard]] inline int GetWidth() const { return Width;  }
		[[nodiscard]] inline int GetHeight() const { return Height; }
		[[nodiscard]] inline unsigned int GetID() const { return ID; }

		// Fields
		unsigned int ID;
		std::string FilePath;
		unsigned char* LocalBuffer;
		int Width, Height, BPP;

	private:
		bool LoadImage(const std::string _Name);
	};
}
