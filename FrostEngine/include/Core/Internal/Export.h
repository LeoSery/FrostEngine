#pragma once

/*
* \file Export.h
* 
* \brief Header file for the Export class.
*/

/*!
* \def FROST_ENGINE_API
* 
* \brief This macro is placed in front of the class name you want to export
* to the engine dll. As the engine is a dll, you need to specify with this
* macro which class can be accessed in the project using FrostEngine.
*/
#ifdef FROSTENGINE_EXPORTS
#define FROST_ENGINE_API __declspec(dllexport)
#else
#define FROST_ENGINE_API __declspec(dllimport)
#endif
