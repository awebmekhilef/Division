#pragma once

#include <GLFW/glfw3.h>

class Time
{
public:
	static float GetTime() { return (float)glfwGetTime(); }
};