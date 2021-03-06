#pragma once

#include "Renderer/Shader.h"

#include <unordered_map>

#include <glad/glad.h>

namespace RUC
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		~OpenGLShader();

		void Bind() override;
		void Unbind() override;

		virtual std::unordered_map <std::string, Uniform>& GetUniforms() override { return m_Uniforms; }

		void UploadUniform(int location, Uniform::Type type, void* data) override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& value) override;
		void UploadUniformInt(const std::string& name, int value) override;
	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void FindUniforms(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& sources);
	private:
		uint32_t m_RendererID;
		std::unordered_map<std::string, Uniform> m_Uniforms;
	};
}