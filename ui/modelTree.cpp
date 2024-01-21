#include "modelTree.h"

void ui::ModelTree::render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(kModelTree_width,kWindow_height- kMainMenubar_height), ImGuiCond_Always);
    // 开始 ImGui 窗口
    ImGui::Begin("Tree Example",nullptr, ImGuiWindowFlags_NoTitleBar);
    // 创建树状结构
    if (ImGui::TreeNode(u8"main node"))
    {
        // 在树节点中添加子节点
        if (ImGui::TreeNode("cylinder1"))
        {
            ImGui::Text("Content of Child Node 1");
            ImGui::TreePop(); // 结束 Child Node 1

        }

        // 添加更多的子节点
        if (ImGui::TreeNode("cone 1"))
        {
            ImGui::Text("Content of Child Node 2");
            ImGui::TreePop(); // 结束 Child Node 2
        }

        // 结束 Root Node
        ImGui::TreePop();
    }

    // 结束 ImGui 窗口
    ImGui::End();
}

ui::ModelTree::ModelTree()
{
}
