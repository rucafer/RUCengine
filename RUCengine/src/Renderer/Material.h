#pragma once

#include "ResourceManager/Resource.h"

#include "Shader.h"
#include "Texture.h"

#include <memory>

namespace RUC
{
	class Material : public Resource
	{
	public:
		static Material* Create(const std::string& name, const std::shared_ptr<Shader>& shader) { return new Material(name, shader); }

		~Material();

		void Bind();

		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetBool(const std::string& name, bool value);
		void SetFloat3(const std::string& name, float x, float y, float z);
		void SetFloat3(const std::string& name, glm::vec3 value);
		void SetFloat4(const std::string& name, float x, float y, float z, float w);
		void SetFloat4(const std::string& name, glm::vec4 value);
		void SetColor(const std::string& name, float r, float g, float b);
		void SetColor(const std::string& name, float r, float g, float b, float a);
		void SetColor(const std::string& name, glm::vec3 value);
		void SetColor(const std::string& name, glm::vec4 value);
		void SetMat4(const std::string& name, glm::mat4 value);
		void SetTexture2D(const std::string& name, const std::shared_ptr<Texture2D>& texture);

		int GetInt(const std::string& name) const;
		float GetFloat(const std::string& name) const;
		bool GetBool(const std::string& name) const;
		glm::vec3 GetFloat3(const std::string& name) const;
		glm::vec4 GetFloat4(const std::string& name) const;
		glm::vec4 GetColor(const std::string& name) const;
		glm::mat4 GetMat4(const std::string& name) const;
		std::shared_ptr<Texture2D> GetTexture2D(const std::string& name) const;

		std::shared_ptr<Shader> GetShader() const { return m_Shader; }


	private:
		Material(const std::string& name, const std::shared_ptr<Shader>& shader);

		void SetUniformValue(const std::string& name, void* value, Uniform::Type type);
		void* GetUniformValue(const std::string& name, Uniform::Type type) const;

		void AllocateUniformBuf();
		void SetTextureIndices();

	private:
		std::shared_ptr<Shader> m_Shader;
		std::unordered_map <std::string, Uniform>& m_Uniforms;
		std::vector<std::shared_ptr<Texture>> m_Textures;


		char* m_UniformBufferPtr;
		size_t m_UniformBufferSize;
	};
}