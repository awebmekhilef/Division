#include "Core/Window.h"

int main()
{
	Window win("Division Engine", 1280, 720);

	while (win.IsOpen())
	{
		win.Clear();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		win.Update();
	}
}
