#include "mainMenuBar.h"
#include <iostream>

void ui::MainMenuBar::render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(kWindow_width, kMainMenubar_height), ImGuiCond_Always);

    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // 添加 File 菜单项
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* 处理打开操作 */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* 处理保存操作 */ }
            if (ImGui::MenuItem("Exit", "Alt+F4")) { /* 处理退出操作 */ }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("edit"))
        {
            // 添加 File 菜单项
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* 处理打开操作 */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* 处理保存操作 */ }
            if (ImGui::MenuItem("Exit", "Alt+F4")) { /* 处理退出操作 */ }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
    // 结束 ImGui 窗口
    ImGui::End();
}
