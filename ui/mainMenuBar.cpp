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
            // ��� File �˵���
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* ����򿪲��� */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* ��������� */ }
            if (ImGui::MenuItem("Exit", "Alt+F4")) { /* �����˳����� */ }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("edit"))
        {
            // ��� File �˵���
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* ����򿪲��� */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* ��������� */ }
            if (ImGui::MenuItem("Exit", "Alt+F4")) { /* �����˳����� */ }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
    // ���� ImGui ����
    ImGui::End();
}
