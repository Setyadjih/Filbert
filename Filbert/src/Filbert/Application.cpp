#include "fbpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

namespace Filbert
{
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case Filbert::ShaderDataType::None:    return GL_FLOAT;
            case Filbert::ShaderDataType::Float:   return GL_FLOAT;
            case Filbert::ShaderDataType::Float2:  return GL_FLOAT;
            case Filbert::ShaderDataType::Float3:  return GL_FLOAT;
            case Filbert::ShaderDataType::Float4:  return GL_FLOAT;
            case Filbert::ShaderDataType::Mat3:    return GL_FLOAT;
            case Filbert::ShaderDataType::Mat4:    return GL_FLOAT;
            case Filbert::ShaderDataType::Int:     return GL_INT;
            case Filbert::ShaderDataType::Int2:    return GL_INT;
            case Filbert::ShaderDataType::Int3:    return GL_INT;
            case Filbert::ShaderDataType::Int4:    return GL_INT;
            case Filbert::ShaderDataType::Bool:    return GL_BOOL;
        }

        FB_CORE_ASSERT(flase, "Uknown ShaderDataType");
        return 0;
    }

    Application::Application()
    {
        // Application Init ----------------------------------------------------
        FB_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // Create Vertex Array -------------------------------------------------
        m_VertexArray.reset(Array::Create());
        m_VertexArray->Bind();

        // Create Vertex Buffer ------------------------------------------------
        float vertices[3 * 7] = {
            // Position             // Color
            -0.5f, -0.5f, 0.0f,     0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f,     0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f,     0.8f, 0.8f, 0.2f, 1.0f,
        };
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->Bind();

        // Destroying layout so we make sure we're accessing the it from the VertexBuffer
        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position"},
                { ShaderDataType::Float4, "a_Color"},
            };
            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            // TODO: !! Abstract this out !!
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index, 
                element.GetComponentCount(), 
                ShaderDataTypeToOpenGLBaseType(element.Type), 
                element.Normalized ? GL_TRUE : GL_FALSE, 
                layout.GetStride(), 
                (const void*)element.Offset
            );
            index++;
        }


        // Create Index Buffer -------------------------------------------------
        unsigned int indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_IndexBuffer->Bind();

        // Vertex & Fragment Shaders -------------------------------------------
        std::string vertexSrc = R"Src(
            #version 330 core

            layout(location=0) in vec3 a_Position;
            layout(location=1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }

        )Src";

        std::string fragmentSrc = R"Src(
            #version 330 core

            layout(location=0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4((v_Position * 0.5) + 0.75, 1.0);
                color = v_Color;
            }

        )Src";

        m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        // Go backwards to go top to bottom of layers (e.g. UI over gameplay)
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled) { break; }
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run()
    {
        while (m_Running) 
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            m_VertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack) { layer->OnUpdate(); }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) { layer->OnImGuiRender(); }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
