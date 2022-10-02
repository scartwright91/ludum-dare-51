#include "Camera.h"


Camera::Camera() :
    Position(glm::vec3(0.0f, 0.0f, 0.0f)), Up(glm::vec3(0.0f, 1.0f, 0.0f)), Front(glm::vec3(0.0f, 0.0f, -1.0f)), Yaw(YAW), Pitch(PITCH)
{
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Right = glm::normalize(glm::cross(Front, WorldUp));
}

Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) :
	Position(position), Up(up), Front(glm::vec3(0.0f, 0.0f, -1.0f)), Yaw(YAW), Pitch(PITCH)
{
	WorldUp = up;
    Right = glm::normalize(glm::cross(Front, WorldUp));
}

Camera::~Camera()
{

}

void Camera::update(graphics::Window* window)
{
    // keyboard input
    if (window->isKeyPressed(GLFW_KEY_UP))
        Position += Front * MovementSpeed;
    if (window->isKeyPressed(GLFW_KEY_DOWN))
        Position -= Front * MovementSpeed;
    if (window->isKeyPressed(GLFW_KEY_LEFT))
        Position -= Right * MovementSpeed;
    if (window->isKeyPressed(GLFW_KEY_RIGHT))
        Position += Right * MovementSpeed;

    // mouse input

}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
