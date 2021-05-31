#include "fbpch.h"
#include "OpenGLArray.h"

#include <glad/glad.h>

namespace Filbert
{
    OpenGLArray::OpenGLArray()
    {
        glCreateVertexArrays(1, &m_VertexArray);
    }
    void OpenGLArray::Bind() const
    {
        glBindVertexArray(m_VertexArray);
    }
    void OpenGLArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}
