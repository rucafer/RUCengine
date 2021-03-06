#pragma once

#include "ResourceManager/Resource.h"

#include <string>

#include <glm.hpp>

namespace RUC
{
	enum class ShaderDataType
	{
		None,
		Int,
		Float,
		Bool,
		Float3,
		Float4,
		Mat4,
		Texture2D
	};


	class Shader : virtual public Resource
	{
	public:
		virtual ~Shader() = default;

		static Shader* LoadFromFile(const std::string& filePath);
		static Shader* Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& value) = 0;
		virtual void UploadUniformInt(const std::string& name, int value) = 0;

		virtual std::unordered_map <std::string, ShaderDataType> GetUniforms() const = 0;
	};
}