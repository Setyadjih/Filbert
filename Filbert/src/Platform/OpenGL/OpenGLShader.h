#pragma once

#include "Filbert/Renderer/Shader.h"

namespace Filbert
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();
        
        virtual void Bind() const;
        virtual void Unbind() const;
    private:
        uint32_t m_RendererID;
    };
}