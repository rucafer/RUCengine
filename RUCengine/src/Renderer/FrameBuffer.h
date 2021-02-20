#pragma once

#include <vector>

namespace RUC
{
	enum class FrameBufferTextureFormat
	{
		None = 0,

		//COLOR
		RGBA8,

		//DEPTH-STENCIL
		DEPTH24STENCIL8
	};

	struct FrameBufferTextureSpecification
	{
		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format)
			:Format(format)	{}

		FrameBufferTextureFormat Format = FrameBufferTextureFormat::None;
		//TODO: filtering, wrap...
	};

	//Helper struct that allows the creation of Texture specifications with initializer lists
	struct FrameBufferAttachmentList
	{
		FrameBufferAttachmentList() = default;
		FrameBufferAttachmentList(std::initializer_list <FrameBufferTextureSpecification> attachments)
			:TextureSpecs(attachments) {}

		std::vector<FrameBufferTextureSpecification> TextureSpecs;
	};

	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		FrameBufferAttachmentList AttachmentList;
		uint32_t Samples = 1;	//TODO: multisampling

		bool SwapChainTarget = false;

		bool resizable = true;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		static FrameBuffer* Create(const FrameBufferSpecification& spec);
		
		static void ResizeAllResizables(uint32_t width, uint32_t height);

	protected:
		static std::vector<FrameBuffer*> s_ResizableFrameBuffers;
	};
}