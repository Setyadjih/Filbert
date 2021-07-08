#include "fbpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Filbert
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}