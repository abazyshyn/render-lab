#pragma once

#include <GLFW/glfw3.h>

namespace Lab
{

    /**
     * @brief Creates ImGUI context
     */
    void SetupImGuiContext(GLFWwindow *const pWindow);

    /**
     * @brief Destroys ImGUI context
     */
    void ShutdownImGui();

} // namespace Lab
