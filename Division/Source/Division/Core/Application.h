#pragma once

#include "Window.h"

#include <string>

class Application
{
public:
	Application(const std::string& name);
	virtual ~Application();

	void Run();
	void Close();

	virtual void OnUpdate(float dt) {};

	static Application& Get() { return *s_Instance; }

private:
	Window* m_Window;

	bool m_Running = true;
	float m_LastFrameTime = 0.0f;

private:
	static Application* s_Instance;
};

