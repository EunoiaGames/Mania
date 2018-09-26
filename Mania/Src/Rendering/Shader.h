#pragma once

#include <GL\glew.h>
#include "../Utils/String.h"
#include <map>
#include "../Math/Math.h"
#include "../Core/Common.h"

class Shader
{
public:
	Shader(const String& shaderFile);
	~Shader();

	void Bind();
	void BindTexture(const String& name, GLuint texture);

	void SetUniformf(const String& name, float value);
	void SetUniformi(const String& name, int32 value);
	void SetUniformui(const String& name, uint32 value);
	void SetUniformVec2(const String& name, const Vector2f& vec);
	void SetUniformVec3(const String& name, const Vector3f& vec);
	void SetUniformVec4(const String& name, const Vector4f& vec);
	void SetUniformMat3(const String& name, const Matrix3f& mat);
	void SetUniformMat4(const String& name, const Matrix4f& mat);

private:
	GLuint CreateShader(const String & src, GLenum type) const;
	void LinkAndValidate() const;
	void ParseShader(const String& src);

	static void CheckForError(GLuint shader, GLuint flag, bool isProgram, const String& errorMessage);
private:
	GLuint m_program;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;

	std::map<String, GLuint> m_uniformLocations;
	std::map<String, uint32> m_textureUnits;
};
