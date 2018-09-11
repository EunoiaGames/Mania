#include "Renderer.h"
#include "../StaticLibs/stb_image.h"

Renderer::Renderer()
{
	m_pVertex = NULL;
	m_renderableCount = 0;

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	const uint32 NUM_INDICES = MAX_RENDERABLES_PER_BATCH * 6;

	GLuint indices[NUM_INDICES];

	uint32 offset = 0;
	for (uint32 i = 0; i < NUM_INDICES; i += 6)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 0;
		indices[i + 4] = offset + 2;
		indices[i + 5] = offset + 3;

		offset += 4;
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * MAX_RENDERABLES_PER_BATCH, NULL, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * NUM_INDICES, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::pos));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}

void Renderer::StartFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::BeginBatch()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	m_pVertex = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	m_renderableCount = 0;
}

void Renderer::Submit(const RenderInfo & renderInfo)
{
	m_pVertex->pos = renderInfo.pos;
	m_pVertex++;

	m_pVertex->pos = Vector2f(renderInfo.pos.x, renderInfo.pos.y + renderInfo.size.y);
	m_pVertex++;

	m_pVertex->pos = renderInfo.pos + renderInfo.size;
	m_pVertex++;

	m_pVertex->pos = Vector2f(renderInfo.pos.x + renderInfo.size.x, renderInfo.pos.y);
	m_pVertex++;

	m_renderableCount++;
}

void Renderer::RenderBatch()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glDrawElements(GL_TRIANGLES, m_renderableCount * 6, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::EndFrame()
{
}
