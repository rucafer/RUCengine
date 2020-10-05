#pragma once

#ifndef RUCAPI
	#ifdef RUC_DYNAMIC_LIBRARY
		#ifdef RUC_CORE
			#define RUCAPI _declspec(dllexport)
		#else
			#define RUCAPI _declspec(dllimport)
		#endif
	#else
		#define RUCAPI
	#endif
#endif

//Helper for bitmasks
#define BIT(x) 1 << x

//LOGGING CONSTANTS
#define RUC_LOG_SEVERITY_FATAL		0
#define RUC_LOG_SEVERITY_ERROR		1
#define RUC_LOG_SEVERITY_WARNING	2
#define RUC_LOG_SEVERITY_INFO		3

#define RUC_LOG_SOURCE_CORE			BIT(0)
#define RUC_LOG_SOURCE_CLIENT		BIT(1)
#define RUC_LOG_SOURCE_SCRIPT		BIT(2)
#define RUC_LOG_SOURCE_ALL			RUC_LOG_SOURCE_CORE | RUC_LOG_SOURCE_CLIENT | RUC_LOG_SOURCE_SCRIPT
