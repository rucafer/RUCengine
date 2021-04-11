#pragma once


namespace RUC
{
	class Uniform
	{
	public:
		enum class Type
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

		//static helper funtions
			
		//Size of each type in bytes
		static size_t TypeSize(Type type)
		{
			switch (type)
			{
			case Type::Int:
				return 4;
			case Type::Float:
				return 4;
			case Type::Bool:
				return 4;
			case Type::Float3:
				return 4 * 3;
			case Type::Float4:
				return 4 * 4;
			case Type::Mat4:
				return 4 * 4 * 4;
			case Type::Texture2D:
				return 4;
			}

			RUC_ASSERT(false, "Unknown UniformType: {0}", type);
			return 0;
		}

		static std::string TypeToString(Type type)
		{
			switch (type)
			{
			case Type::Int:
				return "int";
			case Type::Float:
				return "float";
			case Type::Bool:
				return "bool";
			case Type::Float3:
				return "float3";
			case Type::Float4:
				return "float4";
			case Type::Mat4:
				return "mat4";
			case Type::Texture2D:
				return "texture2D";
			}

			RUC_ASSERT(false, "Unknown UniformType: {0}", type);
			return "";
		}

		static Type TypeFromGLSLString(const std::string type)
		{
			if (type == "int") return Type::Int;
			if (type == "float") return Type::Float;
			if (type == "bool") return Type::Bool;
			if (type == "vec3") return Type::Float3;
			if (type == "vec4") return Type::Float4;
			if (type == "mat4") return Type::Mat4;
			if (type == "sampler2D") return Type::Texture2D;

			RUC_ASSERT(false, "Unknown UniformType: {0}", type);
			return Type::None;
		}

	public:
		Uniform(Type type, int location)
			: m_Type(type), m_Location(location), m_Offset(0)
		{
		}

		Uniform()
			: m_Type(Type::None), m_Location(0), m_Offset(0)
		{
		}

		void setOffset(size_t offest) { m_Offset = offest; }
		void setType(Type type) { m_Type = type; }
		void setLocation(int location) { m_Location = location; }

		size_t getOffset() const { return m_Offset; }
		Type getType() const { return m_Type; }
		int getLocation() const { return m_Location; }

	private:
		Type m_Type;
		int m_Location;
		size_t m_Offset;
	};

}