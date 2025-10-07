#include "pch.hpp"

#include "camera.hpp"
#include "window.hpp"

namespace Lab
{

    CCamera::CCamera()
        : m_CameraPositionVector(0.0f, 0.0f, 0.0f),
          m_CameraFrontVector(0.0f, 0.0f, -1.0f),
          m_CameraUpVector(0.0f, 1.0f, 0.0f),
          m_CameraWorldUpVector(m_CameraUpVector),
          m_CameraRightVector(glm::normalize(glm::cross(m_CameraFrontVector, m_CameraUpVector))),
          m_FOV(45.0f),
          m_CursorPositionX(0.0f),
          m_CursorPositionY(0.0f),
          m_CursorLastPositionX(0.0f),
          m_CursorLastPositionY(0.0f),
          m_MouseSensitivity(0.3f),
          m_Pitch(0.0f),
          m_Yaw(-90.0f),
          m_Roll(0.0f),
          m_IsCursorPositionSet(false)
    {
        UpdateCameraVectors();
    }

    void CCamera::CameraKeyboardInput(GLFWwindow *pWindow, float deltaTime)
    {
        const float fCameraSpeed = 1.0f * deltaTime;

        if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
        {
            m_CameraPositionVector += glm::normalize(m_CameraFrontVector) * fCameraSpeed;
            LAB_TRACE_LOG("W keys pressed.\nX: {0}\nY: {1}\nZ: {2}",
                          m_CameraPositionVector.x,
                          m_CameraPositionVector.y,
                          m_CameraPositionVector.z);
        }
        if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
        {
            m_CameraPositionVector -= glm::normalize(m_CameraFrontVector) * fCameraSpeed;
            LAB_TRACE_LOG("S keys pressed.\nX: {0}\nY: {1}\nZ: {2}",
                          m_CameraPositionVector.x,
                          m_CameraPositionVector.y,
                          m_CameraPositionVector.z);
        }
        if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
        {
            m_CameraPositionVector -= m_CameraRightVector * fCameraSpeed;
            LAB_TRACE_LOG("A keys pressed.\nX: {0}\nY: {1}\nZ: {2}",
                          m_CameraPositionVector.x,
                          m_CameraPositionVector.y,
                          m_CameraPositionVector.z);
        }
        if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_CameraPositionVector += m_CameraRightVector * fCameraSpeed;
            LAB_TRACE_LOG("D keys pressed.\nX: {0}\nY: {1}\nZ: {2}",
                          m_CameraPositionVector.x,
                          m_CameraPositionVector.y,
                          m_CameraPositionVector.z);
        }
    }

    void CCamera::CameraMouseMovementInput(GLFWwindow *pWindow)
    {
        double cursorPositionX = 0.0;
        double cursorPositionY = 0.0;
        glfwGetCursorPos(pWindow, &cursorPositionX, &cursorPositionY);

        m_CursorPositionX = static_cast<float>(cursorPositionX);
        m_CursorPositionY = static_cast<float>(cursorPositionY);

        if (!m_IsCursorPositionSet)
        {
            m_CursorLastPositionX = m_CursorPositionX;
            m_CursorLastPositionY = m_CursorPositionY;
            m_IsCursorPositionSet = true;
        }

        const float cursorOffsetX = m_CursorPositionX - m_CursorLastPositionX;
        const float cursorOffsetY = m_CursorLastPositionY - m_CursorPositionY;

        m_CursorLastPositionX = m_CursorPositionX;
        m_CursorLastPositionY = m_CursorPositionY;

        m_Pitch += cursorOffsetY * m_MouseSensitivity;
        m_Yaw += cursorOffsetX * m_MouseSensitivity;

        if (m_Pitch > 89.0f)
        {
            m_Pitch = 89.0f;
        }
        else if (m_Pitch < -89.0f)
        {
            m_Pitch = -89.0f;
        }

        UpdateCameraVectors();
    }

    glm::mat4 CCamera::CalculateViewMatrix() const
    {
        return glm::lookAt(m_CameraPositionVector,
                           m_CameraPositionVector + m_CameraFrontVector,
                           m_CameraUpVector);
    }

    glm::mat4 CCamera::CalculatePerspectiveProjectionMatrix(const CWindow &window) const
    {
        const auto [width, height] = window.GetWindowSizes();
        const float aspectRatio = width / height;

        constexpr float nearPlane = 0.1f;
        constexpr float farPlane = 100.0f;

        return glm::perspective(glm::radians(m_FOV), aspectRatio, nearPlane, farPlane);
    }

    void CCamera::UpdateCameraVectors()
    {
        glm::vec3 cameraFrontVector(1.0f);
        cameraFrontVector.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
        cameraFrontVector.y = glm::sin(glm::radians(m_Pitch));
        cameraFrontVector.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
        m_CameraFrontVector = glm::normalize(cameraFrontVector);
        m_CameraRightVector = glm::normalize(glm::cross(m_CameraFrontVector, m_CameraWorldUpVector));
        m_CameraUpVector = glm::normalize(glm::cross(m_CameraRightVector, m_CameraFrontVector));
    }

} // namespace Lab
