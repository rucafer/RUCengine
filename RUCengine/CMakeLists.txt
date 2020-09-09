set(RUC_SRC_CORE 
	src/Core/Application.cpp
	src/Core/Application.h
	src/Core/EntryPoint.h)

set(RUC_SRC_PLATFORM 
	src/Platform/Windows/WindowsConsoleLogger.cpp
	src/Platform/Windows/WindowsConsoleLogger.h)

set(RUC_SRC_LOG 
	src/Log/Log.cpp
	src/Log/Log.h)

set(RUC_SRC
	src/Base.h)

if(WIN32)
	add_definitions(-DRUC_WINDOWS)
endif()
add_library(RUCengine STATIC ${RUC_SRC_CORE} ${RUC_SRC_LOG} ${RUC_SRC} ${RUC_SRC_PLATFORM})

source_group("src/Core" FILES ${RUC_SRC_CORE})
source_group("src/Platform" FILES ${RUC_SRC_PLATFORM})
source_group("src/Log" FILES ${RUC_SRC_LOG})
source_group("src" FILES ${RUC_SRC})

target_include_directories(RUCengine PUBLIC "${RUCengine_SOURCE_DIR}/RUCengine/src")