#include "attributeDialog.h"

void ui::AttributeDialog::render()
{
    //ImGui::OpenPopup("DialogPopup");
    //if (ImGui::BeginPopupModal("DialogPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
    //    ImGui::Text("This is a modal dialog.");

    //    if (ImGui::Button("OK", ImVec2(120, 0))) {
    //        // 处理OK按钮点击事件
    //        ImGui::CloseCurrentPopup(); // 关闭对话框
    //        *is_show_ = !*is_show_;
    //    }

    //    ImGui::EndPopup();
    //}
    // 开始创建窗口

    ImGui::SetNextWindowPos(ImVec2(kWindow_width- width_, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(width_, height_), ImGuiCond_Always);


    ImGui::Begin(u8"属性", is_show_);

    // 添加输入框
    static char inputText[256] = "";
    ImGui::InputText(u8"名称", inputText, sizeof(inputText));

    static float x = 0.0f;
    ImGui::InputFloat("x",&x,1,1);
    static float y = 0.0f;
    ImGui::InputFloat("y", &y, 1, 1);
    static float z = 0.0f;
    ImGui::InputFloat("z", &z, 1, 1);

    ImGui::Text("");
    // 在窗口中添加其他控件或操作
    if (ImGui::Button(u8"取消", { 70.f,20.f }))
    {
        std::cout << "点击应用";
        *is_show_ = false;
    };
    ImGui::SameLine();
    if(ImGui::Button(u8"确定", { 70.f,20.f }))
    {
        std::cout << "点击确定";
    };
    ImGui::SameLine();
    if (ImGui::Button(u8"应用", { 70.f,20.f }))
    {
        std::cout << "点击应用";
    };
    // 结束窗口
    ImGui::End();
}

void ui::AttributeDialog::isShow(bool* is_show)
{
    is_show_ = is_show;
}