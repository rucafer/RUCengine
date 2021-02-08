#pragma once

#include <string>

#include <glm.hpp>

namespace RUC
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		static Shader* Create(const std::string& filePath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& value) = 0;
	};
}