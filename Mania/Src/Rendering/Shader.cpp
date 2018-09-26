#include "Shader.h"
#include "../Utils/FileReader.h"

Shader::Shader(const String & shaderName)
{
	m_program = glCreateProgram();

	String src = FileReader::ReadFile(String("Res/Shaders/") + shaderName + ".glsl");
	

	int32 vertexStart = src.FindFirstOf("#vertex");
	int32 fragmentStart = src.FindFirstOf("#fragment");

	String vertexSrc = src.SubString(src.FindFirstOf("#version", vertexStart), fragmentStart);
	String fragmentSrc = src.SubString(src.FindFirstOf("#version", fragmentStart));

	m_vertexShader = CreateShader(vertexSrc, GL_VERTEX_SHADER);
	m_fragmentShader = CreateShader(fragmentSrc, GL_FRAGMENT_SHADER);

	LinkAndValidate();
	ParseShader(src);
}

Shader::~Shader()
{
	glDetachShader(m_program, m_vertexShader);
	glDetachShader(m_program, m_fragmentShader);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::BindTexture(const String & name, GLuint texture)
{
	const auto&& it = m_textureUnits.find(name);
	if (it == m_textureUnits.end())
		return;

	if (texture == 0)
		SetUniformi("HasTexture", 0);
	else
		SetUniformi("HasTexture", 1);

	SetUniformi(name, it->second);
	glActiveTexture(GL_TEXTURE0 + it->second);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Shader::SetUniformf(const String & name, float value)
{
	glUniform1f(m_uniformLocations[name], value);
}

void Shader::SetUniformi(const String & name, int32 value)
{
	glUniform1i(m_uniformLocations[name], value);
}

void Shader::SetUniformui(const String & name, uint32 value)
{
	glUniform1ui(m_uniformLocations[name], value);
}

void Shader::SetUniformVec2(const String & name, const Vector2f & vec)
{
	glUniform2f(m_uniformLocations[name], vec.x, vec.y);
}

void Shader::SetUniformVec3(const String & name, const Vector3f & vec)
{
	glUniform3f(m_uniformLocations[name], vec.x, vec.y, vec.z);
}

void Shader::SetUniformVec4(const String & name, const Vector4f & vec)
{
	glUniform4f(m_uniformLocations[name], vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniformMat3(const String & name, const Matrix3f & mat)
{
	glUniformMatrix3fv(m_uniformLocations[name], 1, true, &mat.values[0][0]);
}

void Shader::SetUniformMat4(const String & name, const Matrix4f & mat)
{
	glUniformMatrix4fv(m_uniformLocations[name], 1, true, &mat.values[0][0]);
}

GLuint Shader::CreateShader(const String & src, GLenum type) const
{
	GLuint shader = glCreateShader(type);

	const GLchar* lines[1] = { src.C_Str() };
	GLint lengths[1] = { (int32)src.Length() };
	glShaderSource(shader, 1, lines, lengths);
	glCompileShader(shader);
	CheckForError(shader, GL_COMPILE_STATUS, false, "Error creating shader");
	glAttachShader(m_program, shader);

	return shader;
}

void Shader::LinkAndValidate() const
{
	glLinkProgram(m_program);
	CheckForError(m_program, GL_LINK_STATUS, true, "Error: Failed to link shader program: ");
	glValidateProgram(m_program);
	CheckForError(m_program, GL_VALIDATE_STATUS, true, "Error: Failed to validate program: ");
}

void Shader::ParseShader(const String & src)
{
	int32 uniformIndex = src.FindFirstOf("uniform", 0);
	uint32 nextTextureUnit = 0;

	while (uniformIndex != -1)
	{
		int32 spaceIndex = src.FindFirstOf(" ", uniformIndex);
		int32 typeIndex = src.FindFirstNotOf(" ", spaceIndex);
		int32 nameIndex = src.FindFirstOf(" ", typeIndex);
		int32 semicolonIndex = src.FindFirstOf(";", nameIndex);

		String typeName = src.SubString(typeIndex, nameIndex);
		String uniformName = src.SubString(nameIndex, semicolonIndex);
		uniformName = uniformName.TrimBeginning();
		uniformName = uniformName.TrimEnd();

		GLint location = glGetUniformLocation(m_program, uniformName.C_Str());
		m_uniformLocations[uniformName] = location;

		if (typeName == "sampler2D")
			m_textureUnits[uniformName] = nextTextureUnit++;

		uniformIndex = src.FindFirstOf("uniform", semicolonIndex);
	}
}

void Shader::CheckForError(GLuint shader, GLuint flag, bool isProgram, const String& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
