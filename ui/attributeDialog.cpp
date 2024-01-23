#include "attributeDialog.h"

void ui::AttributeDialog::render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(kWindow_width, kMainMenubar_height), ImGuiCond_Always);

    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

    ImGui::Text("da");

    ImGui::End();
}