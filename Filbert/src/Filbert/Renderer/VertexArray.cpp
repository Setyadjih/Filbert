#include "fbpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Filbert
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: FB_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        }
        FB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
