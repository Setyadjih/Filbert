#include "fbpch.h"
#include "Array.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLArray.h"

namespace Filbert
{
    Array* Array::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: FB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL: return new OpenGLArray;
        }
        return nullptr;
    }

}
