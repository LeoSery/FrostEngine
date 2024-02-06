#pragma once

#ifdef FROSTENGINE_EXPORTS
#define FROST_ENGINE_API __declspec(dllexport)
#else
#define FROST_ENGINE_API __declspec(dllimport)
#endif
