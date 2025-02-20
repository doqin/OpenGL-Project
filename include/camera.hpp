#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>


enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 90.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
    // Camera attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructor with vectors
    Camera(
        glm::vec3 = glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3 = glm::vec3(0.0f, 1.0f, 0.0f), 
        float = YAW, 
        float = PITCH);
    // Constructor with scalar values
    Camera(float, float, float, float, float, float, float, float);
    // Return the view matrix calculated using Euler angles and LookAt matrix
    glm::mat4 GetViewMatrix();
    // Process input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM
    void ProcessKeyboard(Camera_Movement, float);
    // Process input received from a mouse input system. Expects the offset value in both the x and y direction
    void ProcessMouseMovement(float, float, GLboolean = true);
    // Process input received from a mouse scroll-wheel event
    void ProcessMouseScroll(float yoffset);
private:
    // Calculate the front vector from the Camera's (updated) Euler angles
    void updateCameraVectors();
};