cmake_minimum_required(VERSION 3.6)

project(RUCengine DESCRIPTION "RUCengine is a game engine created for educational purposes" LANGUAGES CXX)
find_package(OpenGL REQUIRED)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(RUC_THIRDPARTY_DIR "${RUCengine_SOURCE_DIR}/ThirdParty")

set(RUC_LIBRARY_TARGET_NAME "RUCengine")
set(RUC_SANDBOX_TARGET_NAME "Sandbox")

#Set build platform
if(WIN32)
#TODO: add possibility of compilig for different plaforms (like Android) from windows
	set(RUC_PLAFORM_WINDOWS TRUE)
endif()

#Set output directory
if(RUC_PLAFORM_WINDOWS)
	set(RUC_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/Windows/")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RUC_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RUC_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUC_OUTPUT_DIRECTORY})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#Add dependencies
add_subdirectory(${RUC_THIRDPARTY_DIR}/spdlog)
add_subdirectory(${RUC_THIRDPARTY_DIR}/glfw)
add_subdirectory(${RUC_THIRDPARTY_DIR}/glad)
add_subdirectory(${RUC_THIRDPARTY_DIR}/ImGui)
add_subdirectory(${RUC_THIRDPARTY_DIR}/glm)

#Engine library
add_subdirectory(RUCengine)

#Sandbox project used for testing. It will be replaced by the actual game executable in the future
add_subdirectory(Sandbox)

target_compile_definitions(${RUC_LIBRARY_TARGET_NAME} PUBLIC "$<$<CONFIG:DEBUG>:RUC_DEBUG>")

#Set VS startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)