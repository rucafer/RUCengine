#pragma once

#include "Renderer/FrameBuffer.h"

namespace RUC
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		~OpenGLFrameBuffer();

		void Bind() override;
		void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override;

		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		void Invalidate();

	private:
		uint32_t m_RendererID = 0;
		FrameBufferSpecification m_Specification;

		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecs;
		FrameBufferTextureSpecification m_DepthAttachmentSpec = FrameBufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}