#pragma once

#include "Filbert/Renderer/Array.h"

namespace Filbert
{
    class OpenGLArray : public Array
    {
    public:
        OpenGLArray();
        
        virtual void Bind() const;
        virtual void Unbind() const;

    private:
        uint32_t m_VertexArray;
    };
}