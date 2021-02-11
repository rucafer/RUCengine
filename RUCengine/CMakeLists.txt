set(RUC_SRC_CORE 
	src/Core/Application.cpp
	src/Core/Application.h
	src/Core/EntryPoint.h
	src/Core/Window.h
	src/Core/Input.h
	src/Core/KeyCodes.h
	src/Core/MouseButtonCodes.h
	src/Core/ImGuiImpl.cpp
	src/Core/ImGuiImpl.h
	src/Core/Timestep.h
	src/Core/Timestep.cpp)

set(RUC_SRC_CORE_LAYERS 
	src/Core/Layers/Layer.h
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

set(RUC_SRC_RENDERER 
	src/Renderer/Buffer.h
	src/Renderer/Buffer.cpp
	src/Renderer/RenderCommand.h
	src/Renderer/RenderCommand.cpp
	src/Renderer/RenderDevice.h
	src/Renderer/RenderDevice.cpp
	src/Renderer/Renderer.h
	src/Renderer/Renderer.cpp
	src/Renderer/Shader.h
	src/Renderer/Shader.cpp
	src/Renderer/VertexArray.h
	src/Renderer/VertexArray.cpp)

set(RUC_SRC_PLATFORM_WINDOWS
	src/Platform/Windows/WindowsWindow.h
	src/Platform/Windows/WindowsWindow.cpp
	src/Platform/Windows/WindowsInput.cpp)

set(RUC_SRC_PLATFORM_OPENGL
	src/Platform/OpenGL/OpenGLBuffer.h
	src/Platform/OpenGL/OpenGLBuffer.cpp
	src/Platform/OpenGL/OpenGLRenderDevice.h
	src/Platform/OpenGL/OpenGLRenderDevice.cpp
	src/Platform/OpenGL/OpenGLShader.h
	src/Platform/OpenGL/OpenGLShader.cpp
	src/Platform/OpenGL/OpenGLVertexArray.h
	src/Platform/OpenGL/OpenGLVertexArray.cpp)

set(RUC_SRC
	src/Base.h)

if(RUC_PLAFORM_WINDOWS)
	add_definitions(-DRUC_WINDOWS)
endif()

add_definitions(-DRUC_CORE)

add_library(${RUC_LIBRARY_TARGET_NAME} STATIC ${RUC_SRC_CORE} ${RUC_SRC_CORE_LAYERS} ${RUC_SRC_CORE_EVENTS} ${RUC_SRC_LOG} 
	${RUC_SRC_RENDERER} ${RUC_SRC} ${RUC_SRC_PLATFORM_WINDOWS} ${RUC_SRC_PLATFORM_OPENGL})

source_group("src/Core" FILES ${RUC_SRC_CORE})
source_group("src/Core/Layers" FILES ${RUC_SRC_CORE_LAYERS})
source_group("src/Core/Events" FILES ${RUC_SRC_CORE_EVENTS})
source_group("src/Platform/Windows" FILES ${RUC_SRC_PLATFORM_WINDOWS})
source_group("src/Platform/OpenGL" FILES ${RUC_SRC_PLATFORM_OPENGL})
source_group("src/Log" FILES ${RUC_SRC_LOG})
source_group("src/Renderer" FILES ${RUC_SRC_RENDERER})
source_group("src" FILES ${RUC_SRC})

target_link_libraries(${RUC_LIBRARY_TARGET_NAME} glfw)
target_link_libraries(${RUC_LIBRARY_TARGET_NAME} glad)
target_link_libraries(${RUC_LIBRARY_TARGET_NAME} imgui)
target_link_libraries(${RUC_LIBRARY_TARGET_NAME} ${OPENGL_LIBRARIES})

target_include_directories(${RUC_LIBRARY_TARGET_NAME} PUBLIC "${RUCengine_SOURCE_DIR}/RUCengine/src")
target_include_directories(${RUC_LIBRARY_TARGET_NAME} PRIVATE "${RUC_THIRDPARTY_DIR}/spdlog/include")
target_include_directories(${RUC_LIBRARY_TARGET_NAME} PRIVATE "${RUC_THIRDPARTY_DIR}/glfw/include")
target_include_directories(${RUC_LIBRARY_TARGET_NAME} PUBLIC "${RUC_THIRDPARTY_DIR}/glm/glm")