#include "Input.h"

GLFWwindow* Input::m_Window;

void Input::Init(GLFWwindow* win)
{
    m_Window = win;
}

bool Input::IsKeyHeld(int key)
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Input::IsKeyReleased(int key)
{
    return glfwGetKey(m_Window, key) == GLFW_RELEASE;
}
