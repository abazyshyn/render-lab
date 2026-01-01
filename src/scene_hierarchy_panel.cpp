#include "pch.hpp"

#include "scene_hierarchy_panel.hpp"
#include "imgui.h"

namespace Lab
{

    void Lab::CSceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Hierarchy");

        for (const CModel &model : m_Context->GetSceneModels())
        {
            DrawModelTreeNode(model);
        }

        ImGui::End();
    }

    void CSceneHierarchyPanel::DrawModelTreeNode(const CModel &model)
    {
        ImGuiTreeNodeFlags flags = (model.GetName() == m_SelectionContext ? ImGuiTreeNodeFlags_Selected : 0) |
                                   ImGuiTreeNodeFlags_OpenOnArrow;
        ImGui::TreeNodeEx(model.GetName().c_str(), flags);
    }

} // namespace Lab
