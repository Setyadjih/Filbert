#include "fbpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGlBuffer.h"

namespace Filbert
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:    FB_CORE_ASSERT(false, "RenderAPI::None is currentlynot supported!"); return nullptr;
            case RendererAPI::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
        }
        FB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:    FB_CORE_ASSERT(false, "RenderAPI::None is currentlynot supported!"); return nullptr;
            case RendererAPI::OpenGL:  return new OpenGLIndexBuffer(indices, size);
        }
        FB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}