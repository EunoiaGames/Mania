#include "Renderer.h"
#include "../StaticLibs/stb_image.h"

Renderer::Renderer() :
	m_shader("Test")
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	Vector2f vertices[4] = { Vector2f(0.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 0.0f) };
	GLubyte indices[6] = { 0, 1, 2, 0, 2, 3 };

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2f) * 4, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Renderer::~Renderer()
{
	
}

void Renderer::SetProjection(const Matrix4f & projection)
{
	m_shader.Bind();
	m_shader.SetUniformMat4("Projection", projection);
}

void Renderer::StartFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	m_shader.Bind();
}

void Renderer::Render(const RenderInfo & renderInfo)
{
	m_shader.SetUniformVec2("Pos", renderInfo.pos);
	m_shader.SetUniformVec2("Size", renderInfo.size);
	m_shader.SetUniformVec4("Color", renderInfo.color);
	m_shader.BindTexture("Texture", renderInfo.texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
}

void Renderer::EndFrame()
{
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
