set(RUC_SRC_CORE 
	src/Core/Application.cpp
	src/Core/Application.h
	src/Core/EntryPoint.h)

add_library(RUCengine STATIC ${RUC_SRC_CORE})

source_group("src/Core" FILES ${RUC_SRC_CORE})