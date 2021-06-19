#include "Material.h"			

#include "ResourceManager/ResourceManager.h"

#include "gtc/type_ptr.hpp"

namespace RUC
{
	Material::Material(const std::string& name, ResPtr<Shader> shader)
		: Resource(name), m_Shader(shader), m_Uniforms(shader->GetUniforms())
	{
		AllocateUniformBuf();
		//Initialize defaults
		memset(m_UniformBufferPtr, 0, m_UniformBufferSize);
		SetTextureIndices();
	}

	Material::~Material()
	{
		delete m_UniformBufferPtr;
	}

	void Material::Bind()
	{
		m_Shader->Bind();

		for (auto& uniform : m_Uniforms)
		{
			RUC_ASSERT(uniform.second.getOffset() + Uniform::TypeSize(uniform.second.getType()) <= m_UniformBufferSize, "Uniform buffer overflow");
			m_Shader->UploadUniform(uniform.second.getLocation(), uniform.second.getType(), m_UniformBufferPtr + uniform.second.getOffset());
		}

		for (int i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i]->Bind(i);
		}
	}

	void Material::SetInt(const std::string& name, int value)
	{
		SetUniformValue(name, &value, Uniform::Type::Int);
	}

	void Material::SetFloat(const std::string& name, float value)
	{
		SetUniformValue(name, &value, Uniform::Type::Float);
	}

	void Material::SetBool(const std::string& name, bool value)
	{
		SetUniformValue(name, &value, Uniform::Type::Bool);
	}

	void Material::SetFloat3(const std::string& name, float x, float y, float z)
	{
		float value[3];
		value[0] = x;
		value[1] = y;
		value[2] = z;

		SetUniformValue(name, &value, Uniform::Type::Float3);
	}

	void Material::SetFloat3(const std::string& name, glm::vec3 value)
	{
		SetUniformValue(name, &value, Uniform::Type::Float3);
	}

	void Material::SetFloat4(const std::string& name, float x, float y, float z, float w)
	{
		float value[4];
		value[0] = x;
		value[1] = y;
		value[2] = z;
		value[3] = w;

		SetUniformValue(name, &value, Uniform::Type::Float4);
	}

	void Material::SetFloat4(const std::string& name, glm::vec4 value)
	{
		SetUniformValue(name, glm::value_ptr(value), Uniform::Type::Float4);
	}

	void Material::SetColor(const std::string& name, float r, float g, float b)
	{
		float value[4];
		value[0] = r;
		value[1] = g;
		value[2] = b;
		value[3] = 1.0f;

		SetUniformValue(name, &value, Uniform::Type::Float4);
	}

	void Material::SetColor(const std::string& name, float r, float g, float b, float a)
	{
		float value[4];
		value[0] = r;
		value[1] = g;
		value[2] = b;
		value[3] = a;

		SetUniformValue(name, &value, Uniform::Type::Float4);
	}

	void Material::SetColor(const std::string& name, glm::vec3 value)
	{
		glm::vec4 valueWithAlpha(value, 1.0f);
		SetUniformValue(name, glm::value_ptr(valueWithAlpha), Uniform::Type::Float4);
	}

	void Material::SetColor(const std::string& name, glm::vec4 value)
	{
		SetUniformValue(name, glm::value_ptr(value), Uniform::Type::Float4);
	}

	void Material::SetMat4(const std::string& name, glm::mat4 value)
	{
		SetUniformValue(name, glm::value_ptr(value), Uniform::Type::Mat4);
	}

	void Material::SetTexture2D(const std::string& name, const ResPtr<Texture2D>& texture)
	{
		auto pos = m_Uniforms.find(name);
		if (pos == m_Uniforms.end())
		{
			RUC_WARN("Attribute {0} could not be found at material {1}", name, GetName());
			return;
		}

		if (pos->second.getType() != Uniform::Type::Texture2D)
		{
			RUC_ERROR("Type mismatch: attribute {0} is of type {1} and the provided value is of type {2}",
				name, Uniform::TypeToString(pos->second.getType()), Uniform::TypeToString(Uniform::Type::Texture2D));
			return;
		}

		int index = *(int*)GetUniformValue(name, Uniform::Type::Texture2D);
		m_Textures[index] = texture;
	}

	int Material::GetInt(const std::string& name) const
	{
		int* valuePtr = (int*)GetUniformValue(name, Uniform::Type::Int);
		if (valuePtr != nullptr)
		{
			return *valuePtr;
		}
		else
		{
			return 0;
		}
	}

	float Material::GetFloat(const std::string& name) const
	{
		float* valuePtr = (float*)GetUniformValue(name, Uniform::Type::Float);
		if (valuePtr != nullptr)
		{
			return *valuePtr;
		}
		else
		{
			return 0.0f;
		}
	}

	bool Material::GetBool(const std::string& name) const
	{
		int* valuePtr = (int*)GetUniformValue(name, Uniform::Type::Bool);
		if (valuePtr != nullptr)
		{
			return *valuePtr != 0;
		}
		else
		{
			return false;
		}
	}

	glm::vec3 Material::GetFloat3(const std::string& name) const
	{
		float* valuePtr = (float*)GetUniformValue(name, Uniform::Type::Float3);
		if (valuePtr != nullptr)
		{
			return glm::vec3(valuePtr[0], valuePtr[1], valuePtr[2]);
		}
		else
		{
			return glm::vec3(0.0f);
		}
	}

	glm::vec4 Material::GetFloat4(const std::string& name) const
	{
		float* valuePtr = (float*)GetUniformValue(name, Uniform::Type::Float4);
		if (valuePtr != nullptr)
		{
			return glm::vec4(valuePtr[0], valuePtr[1], valuePtr[2], valuePtr[3]);
		}
		else
		{
			return glm::vec4(0.0f);
		}
	}

	glm::vec4 Material::GetColor(const std::string& name) const
	{
		float* valuePtr = (float*)GetUniformValue(name, Uniform::Type::Float4);
		if (valuePtr != nullptr)
		{
			return glm::vec4(valuePtr[0], valuePtr[1], valuePtr[2], valuePtr[3]);
		}
		else
		{
			return glm::vec4(0.0f);
		}
	}

	glm::mat4 Material::GetMat4(const std::string& name) const
	{
		float* valuePtr = (float*)GetUniformValue(name, Uniform::Type::Float4);
		if (valuePtr != nullptr)
		{
			return glm::mat4(valuePtr[0], valuePtr[1], valuePtr[2], valuePtr[3],
							 valuePtr[4], valuePtr[5], valuePtr[6], valuePtr[7],
							 valuePtr[8], valuePtr[9], valuePtr[10], valuePtr[11],
							 valuePtr[12], valuePtr[13], valuePtr[14], valuePtr[15]);
		}
		else
		{
			return glm::mat4(0.0f);
		}
	}

	ResPtr<Texture2D> Material::GetTexture2D(const std::string& name) const
	{

		int* valuePtr = (int*)GetUniformValue(name, Uniform::Type::Texture2D);
		if (valuePtr != nullptr)
		{
			return (ResPtr<Texture2D>) m_Textures[*valuePtr];
		}
		else
		{
			return ResPtr<Texture2D>();
		}
	}

	void Material::SetUniformValue(const std::string& name, void* value, Uniform::Type type)
	{
		auto pos = m_Uniforms.find(name);
		if (pos == m_Uniforms.end())
		{
			RUC_WARN("Attribute {0} could not be found at material {1}", name, GetName());
			return;
		}

		//TODO: add compatible types (int and texture2D, vec4 and color...)
		if (pos->second.getType() != type)
		{
			RUC_ERROR("Type mismatch: attribute {0} is of type {1} and the provided value is of type {2}", 
				name, Uniform::TypeToString(pos->second.getType()), Uniform::TypeToString(type));
			return;
		}

		switch (type)
		{
		case Uniform::Type::Int:
		{
			int* dataPtr = (int*)(m_UniformBufferPtr + pos->second.getOffset());
			int* valuePtr = (int*)value;

			*dataPtr = *valuePtr;
			break;
		}
		case Uniform::Type::Float:
		{
			float* dataPtr = (float*)(m_UniformBufferPtr + pos->second.getOffset());
			float* valuePtr = (float*)value;

			*dataPtr = *valuePtr;
			break;
		}
		case Uniform::Type::Bool:
		{
			int* dataPtr = (int*)(m_UniformBufferPtr + pos->second.getOffset());
			bool* valuePtr = (bool*)value;

			*dataPtr = *valuePtr ? 1 : 0;
			break;
		}
		case Uniform::Type::Float3:
		{
			float* dataPtr = (float*)(m_UniformBufferPtr + pos->second.getOffset());
			float* valuePtr = (float*)value;

			*dataPtr = valuePtr[0];
			*dataPtr = valuePtr[1];
			*dataPtr = valuePtr[2];
			break;
		}
		case Uniform::Type::Float4:
		{
			float* dataPtr = (float*)(m_UniformBufferPtr + pos->second.getOffset());
			float* valuePtr = (float*)value;

			dataPtr[0] = valuePtr[0];
			dataPtr[1] = valuePtr[1];
			dataPtr[2] = valuePtr[2];
			dataPtr[3] = valuePtr[3];
			break;
		}
		case Uniform::Type::Mat4:
		{
			float* dataPtr = (float*)(m_UniformBufferPtr + pos->second.getOffset());
			float* valuePtr = (float*)value;

			*dataPtr = valuePtr[0];
			*dataPtr = valuePtr[1];
			*dataPtr = valuePtr[2];
			*dataPtr = valuePtr[3];

			*dataPtr = valuePtr[4];
			*dataPtr = valuePtr[5];
			*dataPtr = valuePtr[6];
			*dataPtr = valuePtr[7];

			*dataPtr = valuePtr[8];
			*dataPtr = valuePtr[9];
			*dataPtr = valuePtr[10];
			*dataPtr = valuePtr[11];

			*dataPtr = valuePtr[12];
			*dataPtr = valuePtr[13];
			*dataPtr = valuePtr[14];
			*dataPtr = valuePtr[15];
			break;
		}
		case Uniform::Type::Texture2D:
		{
			int* dataPtr = (int*)(m_UniformBufferPtr + pos->second.getOffset());
			int* valuePtr = (int*)value;

			*dataPtr = *valuePtr;
			break;
		}
		default:
			RUC_ASSERT(false, "Unknown UniformType: {0}", type);
		}
	}

	void* Material::GetUniformValue(const std::string& name, Uniform::Type type) const
	{
		auto pos = m_Uniforms.find(name);
		if (pos == m_Uniforms.end())
		{
			RUC_WARN("Attribute {0} could not be found at material {1}", name, GetName());
			return nullptr;
		}

		//TODO: add compatible types (int and texture2D, vec4 and color...)
		if (pos->second.getType() != type)
		{
			RUC_ERROR("Type mismatch: attribute {0} is of type {1} and not of type {2}",
				name, Uniform::TypeToString(pos->second.getType()), Uniform::TypeToString(type));
			return nullptr;
		}

		return (void*)(m_UniformBufferPtr + pos->second.getOffset());
	}

	void Material::AllocateUniformBuf()
	{
		m_UniformBufferSize = 0;

		for (auto& uniform : m_Uniforms)
		{
			uniform.second.setOffset(m_UniformBufferSize);
			m_UniformBufferSize += Uniform::TypeSize(uniform.second.getType());
		}

		m_UniformBufferPtr = new char[m_UniformBufferSize];
	}

	void Material::SetTextureIndices()
	{
		int index = 0;
		for (auto& uniform : m_Uniforms)
		{
			if (uniform.second.getType() == Uniform::Type::Texture2D)
			{
				auto texture = ResourceManager::GetByName<Texture2D>("EmptyTexture");
				m_Textures.push_back(ResourceManager::GetByName<Texture2D>("EmptyTexture"));
				int* valuePtr = (int*)(m_UniformBufferPtr + uniform.second.getOffset());
				*valuePtr = index;
				index++;
			}
		}
	}
}