#include "attributeDialog.h"

void ui::AttributeDialog::render()
{
    //ImGui::OpenPopup("DialogPopup");
    //if (ImGui::BeginPopupModal("DialogPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
    //    ImGui::Text("This is a modal dialog.");

    //    if (ImGui::Button("OK", ImVec2(120, 0))) {
    //        // ����OK��ť����¼�
    //        ImGui::CloseCurrentPopup(); // �رնԻ���
    //        *is_show_ = !*is_show_;
    //    }

    //    ImGui::EndPopup();
    //}
    // ��ʼ��������

    ImGui::SetNextWindowPos(ImVec2(kWindow_width- width_, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(width_, height_), ImGuiCond_Always);


    ImGui::Begin(u8"����", is_show_);

    // ��������
    static char inputText[256] = "";
    ImGui::InputText(u8"����", inputText, sizeof(inputText));

    static float x = 0.0f;
    ImGui::InputFloat("x",&x,1,1);
    static float y = 0.0f;
    ImGui::InputFloat("y", &y, 1, 1);
    static float z = 0.0f;
    ImGui::InputFloat("z", &z, 1, 1);

    ImGui::Text("");
    // �ڴ�������������ؼ������
    if (ImGui::Button(u8"ȡ��", { 70.f,20.f }))
    {
        std::cout << "���Ӧ��";
        *is_show_ = false;
    };
    ImGui::SameLine();
    if(ImGui::Button(u8"ȷ��", { 70.f,20.f }))
    {
        std::cout << "���ȷ��";
    };
    ImGui::SameLine();
    if (ImGui::Button(u8"Ӧ��", { 70.f,20.f }))
    {
        std::cout << "���Ӧ��";
    };
    // ��������
    ImGui::End();
}

void ui::AttributeDialog::isShow(bool* is_show)
{
    is_show_ = is_show;
}