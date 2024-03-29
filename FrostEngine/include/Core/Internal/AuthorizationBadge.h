#pragma once

/*!
* \file AuthorizationBadge.h
* 
* \brief Header file for the Authorization class.
*/

/*!
* \namespace frost::core
*
* \brief The namespace for the FrostEngine core functionalities.
*/
namespace frost::core
{
	/*!
	* \class AuthorizationBadge
	* 
	* \brief This file contains the AuthorizationBadge class,
	* which is used to grant access to private constructors.
	* 
	* \details You can add an authorization badge as a parameter
	* to a method by specifying which class is the target of the badge,
	* so that this method can only be called by the class specified
	* in the badge template.
	*/
	template<typename T>
	class AuthorizationBadge
	{
		friend T;

		/*!
		* \brief Constructor that creates a class object passed in parameter.
		* 
		* \detail This constructor can be sent to the method that requires a 
		* badge of the class passed in parameter.
		*/
		AuthorizationBadge() {}
	};
}
