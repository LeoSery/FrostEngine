#pragma once

#include <string>

namespace frost::core
{
	class RTTI
	{
	public:
		virtual const std::string GetTypeName() const = 0;
	};
}

#define FROST_DEFINE_RTTI(_Type)												\
public:																			\
	static const std::string GetStaticTypeName() { return #_Type; };			\
	virtual const std::string GetTypeName() const override { return #_Type; };  \
private:
