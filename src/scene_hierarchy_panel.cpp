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
            ImGui::Text("%s", model.GetName().c_str());
        }

        ImGui::End();
    }

} // namespace Lab
