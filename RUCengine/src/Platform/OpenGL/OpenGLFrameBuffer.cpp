#include "OpenGLFrameBuffer.h"
#include "Log/Log.h"

#include "Base.h"

#include<glad/glad.h>

namespace RUC
{
	static const uint32_t s_MaxFramebufferSize = 8192;

	static bool IsDepthFormat(FrameBufferTextureFormat format)
	{
		switch (format)
		{
			case FrameBufferTextureFormat::DEPTH24STENCIL8: return true;
		}

		return false;
	}

	static GLenum TextureTarget(bool multisampled)
	{
		return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}

	static void CreateTextures(bool multisampled, uint32_t* ids, uint32_t count)
	{
		glCreateTextures(TextureTarget(multisampled), count, ids);
	}

	static void BindTexture(bool multisampled, uint32_t id)
	{
		glBindTexture(TextureTarget(multisampled), id);
	}

	static void AttachColorTexture(uint32_t id, uint32_t samples, GLenum format, uint32_t width, uint32_t height, size_t index)
	{
		bool multisampled = samples > 1;

		if (multisampled)
		{
			glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else
		{
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)(GL_COLOR_ATTACHMENT0 + index), TextureTarget(multisampled), id, 0);
	}

	static void AttachDepthTexture(uint32_t id, uint32_t samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
	{
		bool multisampled = samples > 1;

		if (multisampled)
		{
			glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else
		{
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
		:m_Specification(spec)
	{
		for (auto spec : m_Specification.AttachmentList.TextureSpecs)
		{
			if (IsDepthFormat(spec.Format))
			{
				m_DepthAttachmentSpec = spec;
			}
			else
			{
				m_ColorAttachmentSpecs.push_back(spec);
			}
		}

		Invalidate();

		if (spec.resizable)
		{
			s_ResizableFrameBuffers.push_back(this);
		}
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_DepthAttachment);
		glDeleteTextures((GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());

		auto pos = std::find(s_ResizableFrameBuffers.begin(), s_ResizableFrameBuffers.end(), this);
		s_ResizableFrameBuffers.erase(pos);
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFrameBuffer::Unbind()
	{
		if (m_Specification.SwapChainTarget)
		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, m_RendererID);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

			GLbitfield flags = 0;
			if (m_ColorAttachments.size() != 0) flags |= GL_COLOR_BUFFER_BIT;
			if (m_DepthAttachmentSpec.Format != FrameBufferTextureFormat::None) flags |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
			glBlitFramebuffer(0, 0, m_Specification.Width, m_Specification.Height, 0, 0, m_Specification.Width, m_Specification.Height, flags, GL_NEAREST);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			RUC_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}

		m_Specification.Width = width;
		m_Specification.Height = height;

		Invalidate();
	}

	uint32_t OpenGLFrameBuffer::GetColorAttachmentRendererID(uint32_t slot) const
	{
		RUC_ASSERT(slot < m_ColorAttachments.size(), "Slot {0} is out of range", slot);
		return m_ColorAttachments[slot];
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_RendererID)
		{
			//Delete the old FrameBuffer
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_DepthAttachment);
			glDeleteTextures((GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());

			m_DepthAttachment = 0;
			m_ColorAttachments.clear();
		}

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool multisample = m_Specification.Samples > 1;

		if (!m_ColorAttachmentSpecs.empty())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());
			CreateTextures(multisample, m_ColorAttachments.data(), (uint32_t)m_ColorAttachments.size());

			for (size_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				BindTexture(multisample, m_ColorAttachments[i]);

				switch (m_ColorAttachmentSpecs[i].Format)
				{
					case FrameBufferTextureFormat::RGBA8:
						AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, m_Specification.Width, m_Specification.Height, i);
						break;
				}
			}
		}

		if (m_DepthAttachmentSpec.Format != FrameBufferTextureFormat::None)
		{
			CreateTextures(multisample, &m_DepthAttachment, 1);
			BindTexture(multisample, m_DepthAttachment);

			switch (m_DepthAttachmentSpec.Format)
			{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
				break;
			}
		}

		if (m_ColorAttachments.size() >= 1)
		{
			RUC_ASSERT(m_ColorAttachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((GLsizei)m_ColorAttachmentSpecs.size(), buffers);
		}
		else
		{
			glDrawBuffer(GL_NONE);
		}

		RUC_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}