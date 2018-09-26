#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "../Core/DisplayInput.h"
#include "../Core/Common.h"

class Display
{
public:
	Display(uint32 width, uint32 height);
	~Display();

	bool IsCloseRequested() const;

	void Update() const;

	GLFWwindow* GetHandle() const;

	DisplayInput* GetInput() const;

	inline static Display* GetDisplay() { return s_pDisplay; }
private:
	static Display* s_pDisplay;

	GLFWwindow* m_pWindow;
	DisplayInput* m_pInput;
};
