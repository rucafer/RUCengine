#pragma once

#include "Base.h"

#include <cstdint>
#include <string>

namespace RUC
{
#pragma region BufferLayout

	enum class BufferDataType
	{
		Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Bool, Mat3, Mat4
	};

	static uint32_t BufferDataTypeSize(BufferDataType type)
	{
		switch (type)
		{
		case BufferDataType::Float:		return sizeof(float);
		case BufferDataType::Float2:	return sizeof(float) * 2;
		case BufferDataType::Float3:	return sizeof(float) * 3;
		case BufferDataType::Float4:	return sizeof(float) * 4;
		case BufferDataType::Int:		return sizeof(int);
		case BufferDataType::Int2:		return sizeof(int) * 2;
		case BufferDataType::Int3:		return sizeof(int) * 3;
		case BufferDataType::Int4:		return sizeof(int) * 4;
		case BufferDataType::Mat3:		return sizeof(float) * 3 * 3;
		case BufferDataType::Mat4:		return sizeof(float) * 4 * 4;
		case BufferDataType::Bool:		return sizeof(bool);
		}

		RUC_ASSERT(false, "Unkonwn BufferDataType");
		return 0;
	}

	struct BufferLayoutElement
	{
		std::string Name;
		BufferDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferLayoutElement(BufferDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(BufferDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		int GetComponentCount() const
		{
			switch (Type)
			{
			case BufferDataType::Float:			return 1;
			case BufferDataType::Float2:		return 2;
			case BufferDataType::Float3:		return 3;
			case BufferDataType::Float4:		return 4;
			case BufferDataType::Int:			return 1;
			case BufferDataType::Int2:			return 2;
			case BufferDataType::Int3:			return 3;
			case BufferDataType::Int4:			return 4;
			case BufferDataType::Mat3:			return 3 * 3;
			case BufferDataType::Mat4:			return 4 * 4;
			case BufferDataType::Bool:			return 1;
			}

			RUC_ASSERT(false, "Unkonwn BufferDataType");
			return 0;
		}

	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
			:m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; }

		std::vector<BufferLayoutElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferLayoutElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferLayoutElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferLayoutElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride();
	private:
		std::vector<BufferLayoutElement> m_Elements;
		uint32_t m_Stride = 0;
	};
#pragma endregion

#pragma region VertexBuffer
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, size_t size);
	};

#pragma endregion

#pragma region IndexBuffer
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
#pragma endregion
}