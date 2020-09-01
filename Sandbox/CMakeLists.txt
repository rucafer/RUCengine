link_libraries(RUCengine)

add_executable(Sandbox  "src/SandboxApp.cpp")

target_include_directories(Sandbox PRIVATE "${RUCengine_SOURCE_DIR}/RUCengine/src")