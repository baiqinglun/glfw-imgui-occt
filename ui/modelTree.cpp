#include "modelTree.h"

void ui::ModelTree::render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(kModelTree_width,kWindow_height- kMainMenubar_height), ImGuiCond_Always);
    // ��ʼ ImGui ����
    ImGui::Begin("Tree Example",nullptr, ImGuiWindowFlags_NoTitleBar);
    // ������״�ṹ
    if (ImGui::TreeNode(u8"main node"))
    {
        // �����ڵ�������ӽڵ�
        if (ImGui::TreeNode("cylinder1"))
        {
            ImGui::Text("Content of Child Node 1");
            ImGui::TreePop(); // ���� Child Node 1

        }

        // ��Ӹ�����ӽڵ�
        if (ImGui::TreeNode("cone 1"))
        {
            ImGui::Text("Content of Child Node 2");
            ImGui::TreePop(); // ���� Child Node 2
        }

        // ���� Root Node
        ImGui::TreePop();
    }

    // ���� ImGui ����
    ImGui::End();
}

ui::ModelTree::ModelTree()
{
}
