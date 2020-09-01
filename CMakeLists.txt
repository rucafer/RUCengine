cmake_minimum_required(VERSION 3.6)

project(RUCengine DESCRIPTION "RUCengine is a game engine created for educational purposes" LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Sandbox project used for testing. It will be replaced by the actual game executable in the future
add_subdirectory(Sandbox)

#Engine library
add_subdirectory(RUCengine)

#Set VS startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RUCengine)
