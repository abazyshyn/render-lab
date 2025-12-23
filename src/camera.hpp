#pragma once

#include <GLFW/glfw3.h>

namespace Lab
{
    // Forward declaration
    class CWindow;

    // TODO: Still in development
    class CCamera
    {
    public:
        CCamera();

        void CameraKeyboardInput(GLFWwindow *pWindow, float deltaTime);
        void CameraMouseMovementInput(GLFWwindow *pWindow);
        [[nodiscard]] glm::mat4 CalculateViewMatrix() const;
        [[nodiscard]] glm::mat4 CalculatePerspectiveProjectionMatrix(const CWindow &pWindow) const;

        [[nodiscard]] float GetFOV() const { return m_FOV; }
        [[nodiscard]] glm::vec3 GetCameraPos() const { return m_CameraPositionVector; }
        [[nodiscard]] glm::vec3 GetCameraFront() const { return m_CameraFrontVector; }
        [[nodiscard]] glm::vec3 GetCameraUp() const { return m_CameraUpVector; }

        void SetCameraPosition(const glm::vec3 &cameraPosition) { m_CameraPositionVector = cameraPosition; }
        void SetFOV(const float FOV) { m_FOV = FOV; }
        void SetPosX(const float cursorPositionX) { m_CursorPositionX = cursorPositionX; }
        void SetPosY(const float cursorPositionY) { m_CursorPositionY = cursorPositionY; }
        void SetLastPosX(const float cursorLastPositionX) { m_CursorLastPositionX = cursorLastPositionX; }
        void SetLastPosY(const float cursorLastPositionY) { m_CursorLastPositionY = cursorLastPositionY; }
        void SetSensitivity(const float mouseSensitivity) { m_MouseSensitivity = mouseSensitivity; }
        void SetPitch(const float pitch) { m_Pitch = pitch; }
        void SetYaw(const float yaw) { m_Yaw = yaw; }
        void SetRoll(const float roll) { m_Roll = roll; }

    private:
        glm::vec3 m_CameraPositionVector;
        glm::vec3 m_CameraFrontVector;
        glm::vec3 m_CameraUpVector;
        glm::vec3 m_CameraWorldUpVector;
        glm::vec3 m_CameraRightVector;
        float m_FOV;
        float m_CursorPositionX;
        float m_CursorPositionY;
        float m_CursorLastPositionX;
        float m_CursorLastPositionY;
        float m_MouseSensitivity;
        float m_Pitch;
        float m_Yaw;
        float m_Roll;
        bool m_IsCursorPositionSet;
        unsigned char _pad[3] = {0}; // Explicit padding

        void UpdateCameraVectors();
    };

} // namespace Lab
