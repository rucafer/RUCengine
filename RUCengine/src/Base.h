#pragma once

#include "Log/Log.h"
#include "Core/Events/Event.h"

//Asserts
#ifdef RUC_DEBUG
#define RUC_ASSERT(condition, ...) if(!(condition)){RUC_ERROR("Assertion error: "##__VA_ARGS__); __debugbreak();}
#endif

//Helper for bitmasks
#define BIT(x) 1 << x
