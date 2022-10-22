#include "Application.h"
#include "Time.h"

Application* Application::s_Instance;

Application::Application(const std::string& name)
{
	s_Instance = this;

	m_Window = new Window(name, 1280, 720);

	// TODO: Init renderer
}

Application::~Application()
{
	// TODO: Terminate renderer
}

void Application::Run()
{
	while (m_Window->IsOpen())
	{
		m_Window->Clear();

		float time = Time::GetTime();
		float dt = time - m_LastFrameTime;
		m_LastFrameTime = time;

		OnUpdate(dt);

		m_Window->Update();
	}
}

void Application::Close()
{
	m_Window->Close();
}
