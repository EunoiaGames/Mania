#pragma once

#include "Common.h"
#include <GLFW\glfw3.h>

#define MAX_KEYS GLFW_KEY_LAST
#define MAX_MOUSE_BUTTONS GLFW_MOUSE_BUTTON_LAST

typedef uint32 Key;
typedef uint32 MouseButton;

class DisplayInput
{
public:
	DisplayInput();

	void Update();

	bool IsKeyDown(Key key) const;
	bool IsKeyPressed(Key key) const;
	bool IsKeyReleased(Key key) const;

	bool IsMouseButtonDown(MouseButton button) const;
	bool IsMouseButtonPressed(MouseButton button) const;
	bool IsMouseButtonReleased(MouseButton button) const;

	inline void SetKeyState(Key key, bool state) { m_keys[key] = state; }
	inline void SetButtonState(MouseButton button, bool state) { m_mouseButtons[button] = state; }
private:
	bool m_keys[MAX_KEYS];
	bool m_lastKeys[MAX_KEYS];

	bool m_mouseButtons[MAX_MOUSE_BUTTONS];
	bool m_lastMouseButtons[MAX_MOUSE_BUTTONS];
};
