#include "mainMenuBar.h"
#include <iostream>

bool ui::MainMenuBar::is_open_file_ = false;
bool ui::MainMenuBar::is_open_attr_ = false;

void ui::MainMenuBar::render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(kWindow_width, kMainMenubar_height), ImGuiCond_Always);
    
    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // ��� File �˵���
            if (ImGui::MenuItem("Open model", "Ctrl+O")) { openFile(); }
            if (ImGui::MenuItem("Save model", "Ctrl+S")) { /* ��������� */ }
            if (ImGui::MenuItem("Exit", "Alt+F4")) { /* �����˳����� */ }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            // ��� File �˵���
            if (ImGui::BeginMenu("create"))
            {
                if (ImGui::MenuItem("point", "", &is_open_attr_)) { }
                if (ImGui::MenuItem("line")) { /* ����򿪲��� */ }
                if (ImGui::MenuItem("plane")) { /* ����򿪲��� */ }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("2D graphics"))
            {
                if (ImGui::MenuItem("circle")) { /* ����򿪲��� */ }
                if (ImGui::MenuItem("rectangle")) { /* ����򿪲��� */ }
                if (ImGui::MenuItem("polygon")) { /* ����򿪲��� */ }
                if (ImGui::MenuItem("parallelogram")) { /* ����򿪲��� */ }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
    // ���� ImGui ����
    ImGui::End();

    if (is_open_attr_)
    {
        attributeDialog = std::make_unique<AttributeDialog>();
        attributeDialog.get()->isShow(&is_open_attr_);
        attributeDialog.get()->render();
    }

    if (is_open_file_)
    {
        fileDialog = std::make_unique<OpenFileDialog>();
        fileDialog.get()->render();
    }


}

void ui::MainMenuBar::openFile()
{
    IGFD::FileDialogConfig config;
    config.path = ".";
    config.countSelectionMax = -1;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".*,.stl,.vtk,.stp,.step", config);
    is_open_file_ = true;
}

void ui::MainMenuBar::saveFile()
{
    
}

void ui::MainMenuBar::createPoint()
{
   
}
