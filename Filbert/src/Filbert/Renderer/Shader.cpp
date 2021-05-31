#include "fbpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Filbert
{
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:    FB_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        FB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}