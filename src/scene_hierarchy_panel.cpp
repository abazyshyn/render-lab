#include "pch.hpp"

#include "scene_hierarchy_panel.hpp"
#include "imgui.h"

namespace Lab
{

    void Lab::CSceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        for (CModel &model : m_Context->GetSceneModels())
        {
            DrawModelTreeNode(model);

            if (m_SelectionContext == model.GetName())
            {
                ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

                // DrawComponents(model);

                ImGui::End();
            }
        }

        ImGui::End();
    }

    void CSceneHierarchyPanel::DrawModelTreeNode(CModel &model)
    {
        ImGuiTreeNodeFlags flags = (model.GetName() == m_SelectionContext ? ImGuiTreeNodeFlags_Selected : 0);

        bool opened = ImGui::TreeNodeEx(model.GetName().c_str(), flags);

        if (ImGui::IsItemClicked())
        {
            m_SelectionContext = model.GetName();
        }

        if (opened)
        {
            ImGui::TreePop();
        }
    }

    // void CSceneHierarchyPanel::DrawComponents(CModel &model)
    //{
    //     // TODO: changing the model name
    //     // static char buffer[256] = {};

    //    // if (buffer[0] == '\0')
    //    //     strcpy_s(buffer, sizeof(buffer), model.GetName().c_str());

    //    // if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
    //    //{
    //    //     model.SetModelName(buffer);
    //    //     m_SelectionContext = model.GetName();
    //    // }

    //    glm::mat4 modelMatrix = model.GetModelMatrix();

    //    if (ImGui::DragFloat3("Position", glm::value_ptr(modelMatrix[3]), 0.1f))
    //    {
    //        model.SetModelMatrix(modelMatrix);
    //    }

    //    static glm::vec3 euler(0.0f);
    //    static glm::vec3 scale(1.0f);

    //    if (ImGui::DragFloat3("Rotation", glm::value_ptr(euler), 0.1f) ||
    //        ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.01f))
    //    {
    //        modelMatrix = glm::rotate(modelMatrix, glm::radians(euler.x), glm::vec3(1, 0, 0));
    //        modelMatrix = glm::rotate(modelMatrix, glm::radians(euler.y), glm::vec3(0, 1, 0));
    //        modelMatrix = glm::rotate(modelMatrix, glm::radians(euler.z), glm::vec3(0, 0, 1));

    //        scale = glm::max(scale, 0.001f);
    //        modelMatrix = glm::scale(modelMatrix, scale);

    //        model.SetModelMatrix(modelMatrix);
    //    }
    //}

} // namespace Lab
