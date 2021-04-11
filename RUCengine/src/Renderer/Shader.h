#pragma once

#include "ResourceManager/Resource.h"

#include "Renderer/Uniform.h"

#include <string>

#include <glm.hpp>

namespace RUC
{
	class Shader : virtual public Resource
	{
	public:
		virtual ~Shader() = default;

		static Shader* LoadFromFile(const std::string& filePath);
		static Shader* Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		
		virtual void UploadUniform(int location, Uniform::Type type, void* data) = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& value) = 0;
		virtual void UploadUniformInt(const std::string& name, int value) = 0;

		virtual std::unordered_map <std::string, Uniform>& GetUniforms() = 0;
	};
}