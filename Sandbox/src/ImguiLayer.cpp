#include "ImguiLayer.h"

#include "Core/Application.h"


void ImGuiLayer::OnImGuiRender()
{
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

