#pragma once

#include "../Core/Common.h"
#include <GL\glew.h>
#include <string>
#include "Texture.h"
#include "Shader.h"

struct RenderInfo
{
	Vector2f pos;
	Vector2f size;
	Vector4f color;
	Texture texture;
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	void SetProjection(const Matrix4f& projection);

	void StartFrame();

	void Render(const RenderInfo& renderInfo);

	void EndFrame();
private:
	Shader m_shader;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
};
