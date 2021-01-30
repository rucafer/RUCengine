link_libraries(${RUC_LIBRARY_TARGET_NAME})

add_executable(${RUC_SANDBOX_TARGET_NAME}  "src/SandboxApp.cpp" "src/TestLayer.cpp" "src/TestLayer.h" "src/ImguiLayer.h" "src/ImguiLayer.cpp")

target_link_libraries(${RUC_SANDBOX_TARGET_NAME} imgui)

target_include_directories(${RUC_SANDBOX_TARGET_NAME} PRIVATE "${RUC_THIRDPARTY_DIR}/spdlog/include")
