#pragma once

#include <GLFW/glfw3.h>

class Input
{
public:
	static void Init(GLFWwindow* win);

	static bool IsKeyHeld(int key);
	static bool IsKeyReleased(int key);

private:
	static GLFWwindow* m_Window;
};

