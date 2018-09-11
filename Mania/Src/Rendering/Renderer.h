#pragma once

#include "../Core/Common.h"
#include <GL\glew.h>
#include "../Math/Vector.h"
#include <string>
#include "Texture.h"

#define MAX_RENDERABLES_PER_BATCH 100

struct Vertex
{
	Vector2f pos;
};

struct RenderInfo
{
	Vector2f pos;
	Vector2f size;
	Texture texture;
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	void StartFrame();

	void BeginBatch();
	void Submit(const RenderInfo& renderInfo);
	void RenderBatch();

	void EndFrame();
private:
	Vertex* m_pVertex;
	uint32 m_renderableCount;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
};
