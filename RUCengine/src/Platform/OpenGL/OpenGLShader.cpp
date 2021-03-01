#include "OpenGLShader.h"
#include "Base.h"

#include <vector>
#include <fstream>

#include <glad/glad.h>
#include <gtc/type_ptr.hpp>

namespace RUC
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		RUC_ASSERT(false, "Unknown shader type: {0}", type);

		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filePath)
		:Resource(filePath)
	{
		std::string source = ReadFile(filePath);

		auto shaderSources = PreProcess(source);

		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		:Resource(name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string result;
		std::ifstream in(filePath, std::ios::in, std::ios::binary);

		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			RUC_ERROR("Could not load shader, file not found: {0}", filePath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* token = "#type";
		size_t tokenLength = strlen(token);
		size_t pos = source.find(token, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			RUC_ASSERT(eol != std::string::npos, "Shader syntax error: '#type' tag at the end of the file");

			size_t begin = pos + tokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(token, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& sources)
	{
		std::vector<uint32_t> ids;	//ids are stored so that the shaders can be detached after program compilation

		m_RendererID = glCreateProgram();

		for (const auto& shader : sources)
		{
			uint32_t id = glCreateShader(shader.first);

			const GLchar* source = shader.second.c_str();
			glShaderSource(id, 1, &source, 0);

			glCompileShader(id);

			GLint isCompiled = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(id);

				RUC_ASSERT(false, "Vertex shader compilation error:\n\t{0}", infoLog.data());
				return;
			}

			glAttachShader(m_RendererID, id);
			ids.push_back(id);
		}

		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			for (uint32_t id : ids)
			{
				glDeleteShader(id);
			}

			RUC_ASSERT(false, "Shader linking error:\n\t{0}", infoLog.data());
			return;
		}

		for (uint32_t id : ids)
		{
			glDetachShader(m_RendererID, id);
		}
	}
}
