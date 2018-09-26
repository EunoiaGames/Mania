#include "Display.h"

Display* Display::s_pDisplay;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Display::Display(uint32 width, uint32 height)
{
	if (!glfwInit())
		return;

	glfwDefaultWindowHints();

	m_pWindow = glfwCreateWindow(width, height, "Mania", NULL, NULL);
	if (!m_pWindow)
		return;

	glfwMakeContextCurrent(m_pWindow);
	glfwSetKeyCallback(m_pWindow, key_callback);
	glfwSetMouseButtonCallback(m_pWindow, mouse_button_callback);
	
	if (glewInit() != GLEW_OK)
		return;

	glfwSwapInterval(1);

	m_pInput = new DisplayInput();
	s_pDisplay = this;
}

Display::~Display()
{
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
	delete m_pInput;
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

DisplayInput * Display::GetInput() const
{
	return m_pInput;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		Display::GetDisplay()->GetInput()->SetKeyState(key, true);
	else if (action == GLFW_RELEASE)
		Display::GetDisplay()->GetInput()->SetKeyState(key, false);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(action == GLFW_PRESS)
		Display::GetDisplay()->GetInput()->SetButtonState(button, true);
	else if (action == GLFW_RELEASE)
		Display::GetDisplay()->GetInput()->SetButtonState(button, false);
}
