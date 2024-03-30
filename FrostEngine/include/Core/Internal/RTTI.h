#pragma once

/*!
* \file RTTI.h
* 
* \brief Header file for the RTTI class.
*/

#include <string>

/*!
* \namespace frost::core
*
* \brief The namespace for FrostEngine's core functionalities.
*/
namespace frost::core
{
	/*!
	* \class RTTI
	* 
	* \brief Class to get the type name of a class at runtime.
	*  
	* \details This class return the name of a class pass as parameter using a specific macro.
	*/
	class RTTI
	{
	public:

		/*!
		* \brief Method to get the type name of a class at runtime.
		* 
		* \fn virtual const std::string GetTypeName() const = 0
		* 
		* \return The name of the class type as a string
		* 
		* \details This virtual method is overridden by the 'FROST_DEFINE_RTTI'
		* macro and returns the class name passed as a string parameter to this macro.
		*/
		virtual const std::string GetTypeName() const = 0;
	};
}


/*!
* \def FROST_DEFINE_RTTI(_Type)
* 
* \brief Macro to define the RTTI for a class.
* 
* \details Insert the macro in the class where you want to use RTTI
* and pass the name of the class in which you're defining the macro.
*/
#define FROST_DEFINE_RTTI(_Type)												\
public:																			\
	static const std::string GetStaticTypeName() { return #_Type; };			\
	virtual const std::string GetTypeName() const override { return #_Type; };  \
private:
