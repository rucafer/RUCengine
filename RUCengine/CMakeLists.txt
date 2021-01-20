set(RUC_SRC_CORE 
	src/Core/Application.cpp
	src/Core/Application.h
	src/Core/EntryPoint.h)

set(RUC_SRC_CORE_LAYERS 
	src/Core/Layers/Layer.h
	src/Core/Layers/Layer.cpp
	src/Core/Layers/LayerStack.h
	src/core/Layers/LayerStack.cpp)

set(RUC_SRC_CORE_EVENTS 
	src/Core/Events/Event.h
	src/Core/Events/EventDispatcher.h
	src/Core/Events/ApplicationEvent.h
	src/Core/Events/KeyEvent.h)

set(RUC_SRC_LOG 
	src/Log/Log.h
	src/Log/Log.cpp)

set(RUC_SRC
	src/Base.h)

if(RUC_PLAFORM_WINDOWS)
	add_definitions(-DRUC_WINDOWS)
endif()


add_library(${RUC_LIBRARY_TARGET_NAME} STATIC ${RUC_SRC_CORE} ${RUC_SRC_CORE_LAYERS} ${RUC_SRC_CORE_EVENTS} ${RUC_SRC_LOG} ${RUC_SRC} ${RUC_SRC_PLATFORM_WINDOWS})


source_group("src/Core" FILES ${RUC_SRC_CORE})
source_group("src/Core/Layers" FILES ${RUC_SRC_CORE_LAYERS})
source_group("src/Core/Events" FILES ${RUC_SRC_CORE_EVENTS})
source_group("src/Platform/Windows" FILES ${RUC_SRC_PLATFORM_WINDOWS})
source_group("src/Log" FILES ${RUC_SRC_LOG})
source_group("src" FILES ${RUC_SRC})

target_include_directories(${RUC_LIBRARY_TARGET_NAME} PUBLIC "${RUCengine_SOURCE_DIR}/RUCengine/src")
target_include_directories(${RUC_LIBRARY_TARGET_NAME} PUBLIC "${RUC_THIRDPARTY_DIR}/spdlog/include")