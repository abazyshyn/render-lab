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

        void CameraKeyboardInput(GLFWwindow *t_pWindow, float t_DeltaTime);
        void CameraMouseMovementInput(GLFWwindow *t_pWindow);
        [[nodiscard]] glm::mat4 CalculateViewMatrix() const;
        [[nodiscard]] glm::mat4 CalculatePerspectiveProjectionMatrix(const CWindow &ct_pWindow) const;

        [[nodiscard]] float GetFOV() const { return m_FOV; }
        [[nodiscard]] glm::vec3 GetCameraPos() const { return m_CameraPositionVector; }
        [[nodiscard]] glm::vec3 GetCameraFront() const { return m_CameraFrontVector; }
        [[nodiscard]] glm::vec3 GetCameraUp() const { return m_CameraUpVector; }

        void SetCameraPosition(const glm::vec3 &cameraPosition) { m_CameraPositionVector = cameraPosition; }
        void SetFOV(const float ct_FOV) { m_FOV = ct_FOV; }
        void SetPosX(const float ct_CursorPositionX) { m_CursorPositionX = ct_CursorPositionX; }
        void SetPosY(const float ct_CursorPositionY) { m_CursorPositionY = ct_CursorPositionY; }
        void SetLastPosX(const float ct_CursorLastPositionX) { m_CursorLastPositionX = ct_CursorLastPositionX; }
        void SetLastPosY(const float ct_CursorLastPositionY) { m_CursorLastPositionY = ct_CursorLastPositionY; }
        void SetSensitivity(const float ct_MouseSensitivity) { m_MouseSensitivity = ct_MouseSensitivity; }
        void SetPitch(const float ct_Pitch) { m_Pitch = ct_Pitch; }
        void SetYaw(const float ct_Yaw) { m_Yaw = ct_Yaw; }
        void SetRoll(const float ct_Roll) { m_Roll = ct_Roll; }

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
