#include "Display.h"

Display::Display(uint32 width, uint32 height)
{
	if (!glfwInit())
		return;

	glfwDefaultWindowHints();

	m_pWindow = glfwCreateWindow(width, height, "Mania", NULL, NULL);
	if (!m_pWindow)
		return;

	glfwMakeContextCurrent(m_pWindow);
	
	if (glewInit() != GLEW_OK)
		return;

	glfwSwapInterval(1);
}

Display::~Display()
{
}

bool Display::IsCloseRequested() const
{
	return glfwWindowShouldClose(m_pWindow);
}

void Display::Update() const
{
	glfwPollEvents();
	glfwSwapBuffers(m_pWindow);
}

GLFWwindow * Display::GetHandle() const
{
	return m_pWindow;
}
