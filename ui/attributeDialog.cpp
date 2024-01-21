#include "attributeDialog.h"

void ui::AttributeDialog::render()
{
    bool showMyDialog = false;
    ImGui::Begin("My Dialog", &showMyDialog, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("This is a simple dialog.");

    if (ImGui::Button("OK")) {
        showMyDialog = false;
    }

    ImGui::End();
}