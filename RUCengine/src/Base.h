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