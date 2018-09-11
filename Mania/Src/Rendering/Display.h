#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "../Core/Common.h"

class Display
{
public:
	Display(uint32 width, uint32 height);
	~Display();

	bool IsCloseRequested() const;

	void Update() const;

	GLFWwindow* GetHandle() const;
private:
	GLFWwindow* m_pWindow;
};
