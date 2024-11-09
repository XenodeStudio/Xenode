#include "pch"
#include "Shader.h"

#include <core/app/GameApplication.h>

#include <gfxapi/OpenGL/OpenGLShader.h>

namespace Xen {
	Ref<Shader> Shader::CreateShader(const UnorderedMap<ShaderType, Buffer>& shaders)
	{
		switch (GetApplicationInstance()->GetGraphicsAPI())
		{
		case GraphicsAPI::XEN_OPENGL_API:
			return std::make_shared<OpenGLShader>(shaders);
		}
		return nullptr;
	}
	Ref<Shader> Shader::CreateShader(const std::string& filePath)
	{
		switch (GetApplicationInstance()->GetGraphicsAPI())
		{
		case GraphicsAPI::XEN_OPENGL_API:
			return std::make_shared<OpenGLShader>(filePath);
		}
		return nullptr;
	}

	Ref<Shader> Shader::CreateShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		switch (GetApplicationInstance()->GetGraphicsAPI())
		{
		case GraphicsAPI::XEN_OPENGL_API:
			return std::make_shared<OpenGLShader>(vertexShaderFilePath, fragmentShaderFilePath);
		}
		return nullptr;
	}

	Ref<ComputeShader> ComputeShader::CreateComputeShader(const std::string& filePath)
	{
		switch (GetApplicationInstance()->GetGraphicsAPI())
		{
		case GraphicsAPI::XEN_OPENGL_API:
			return std::make_shared<OpenGLComputeShader>(filePath);
		}
		return nullptr;
	}
}