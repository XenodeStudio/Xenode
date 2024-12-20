#include "pch"
#include "Buffer.h"
#include <core/app/GameApplication.h>

#include <gfxapi/OpenGL/OpenGLBuffer.h>


namespace Xen {
	Ref<VertexBuffer> VertexBuffer::CreateVertexBuffer(Size size, const VertexBufferLayout& layout)
	{
		switch (GetApplicationInstance()->GetGraphicsAPI())
		{
		case GraphicsAPI::XEN_OPENGL_API:
			return std::make_shared<OpenGLVertexBuffer>(size, layout);
		}
		return nullptr;
	}

	Ref<ElementBuffer> ElementBuffer::CreateElementBuffer(Size size, ElementBufferDataType dataType)
	{
		switch (GetApplicationInstance()->GetGraphicsAPI())
		{
		case GraphicsAPI::XEN_OPENGL_API:
			return std::make_shared<OpenGLElementBuffer>(size, dataType);
		}
		return nullptr;
	}
	Ref<UniformBuffer> UniformBuffer::CreateUniformBuffer(Size size, const VertexBufferLayout& layout, uint8_t bindingIndex)
	{

		switch (GetApplicationInstance()->GetGraphicsAPI())
		{
		case GraphicsAPI::XEN_OPENGL_API:
			return std::make_shared<OpenGLUniformBuffer>(size, layout, bindingIndex);
		}
		return nullptr;
	}
	Ref<StorageBuffer> StorageBuffer::CreateStorageBuffer(Size size, const VertexBufferLayout& layout, uint8_t bindingIndex)
	{
		switch (GetApplicationInstance()->GetGraphicsAPI())
		{
		case GraphicsAPI::XEN_OPENGL_API:
			return std::make_shared<OpenGLStorageBuffer>(size, layout, bindingIndex);
		}
		return nullptr;
	}
	Ref<TransformFeedback> TransformFeedback::CreateTransformFeedback(std::vector<std::string> outAttributes, TransformFeedbackPrimitive primitive)
	{
		switch (GetApplicationInstance()->GetGraphicsAPI())
		{
		case GraphicsAPI::XEN_OPENGL_API:
			return std::make_shared<OpenGLTransformFeedback>(outAttributes, primitive);
		}
		return nullptr;
	}
}