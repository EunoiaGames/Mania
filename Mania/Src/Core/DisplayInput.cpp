#include "DisplayInput.h"
#include <cstring>
#include <GLFW\glfw3.h>

DisplayInput::DisplayInput()
{
	memset(m_keys, false, sizeof(bool) * MAX_KEYS);
	memset(m_lastKeys, false, sizeof(bool) * MAX_KEYS);
	memset(m_mouseButtons, false, sizeof(bool) * MAX_MOUSE_BUTTONS);
	memset(m_lastMouseButtons, false, sizeof(bool) * MAX_MOUSE_BUTTONS);
}

void DisplayInput::Update()
{
	memcpy(m_lastKeys, m_keys, sizeof(bool) * MAX_KEYS);
	memcpy(m_lastMouseButtons, m_mouseButtons, sizeof(bool) * MAX_MOUSE_BUTTONS);
}

bool DisplayInput::IsKeyDown(Key key) const
{
	return m_keys[key];
}

bool DisplayInput::IsKeyPressed(Key key) const
{
	return m_keys[key] && !m_lastKeys[key];
}

bool DisplayInput::IsKeyReleased(Key key) const
{
	return !m_keys[key] && m_lastKeys[key];
}

bool DisplayInput::IsMouseButtonDown(MouseButton button) const
{
	return m_mouseButtons[button];
}

bool DisplayInput::IsMouseButtonPressed(MouseButton button) const
{
	return m_mouseButtons[button] && !m_lastMouseButtons[button];
}

bool DisplayInput::IsMouseButtonReleased(MouseButton button) const
{
	return !m_mouseButtons[button] && m_lastMouseButtons[button];
}
