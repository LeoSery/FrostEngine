#pragma once
#include <string>

namespace frost::core
{
	class Texture
	{
	public:
		unsigned int m_ID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;

	public:
		Texture(const std::string& _name);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind();

		inline int GetWidth()	const { return m_Width;	}
		inline int GetHeight()	const { return m_Height;}
		inline unsigned int GetID()		const { return m_ID;	}

	private:
		bool LoadImage(const std::string _name);
	};
}
