#include "fbpch.h"
#include "Application.h"

#include "Filbert/Renderer/Renderer.h"

#include "Input.h"

namespace Filbert
{
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;


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
        m_VertexArray.reset(VertexArray::Create());

        // Create Vertex Buffer ------------------------------------------------
        float vertices[3 * 7] = {
            // Position             // Color
            -0.5f, -0.5f, 0.0f,     0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f,     0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f,     0.8f, 0.8f, 0.2f, 1.0f,
        };
        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        vertexBuffer->Bind();

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position"},
            { ShaderDataType::Float4, "a_Color"},
        };

        // we're setting the attribs in the vertex array, so the buffer needs a layout
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        // Create Index Buffer -------------------------------------------------
        unsigned int indices[3] = {0, 1, 2};
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(VertexArray::Create());

        float squareVertices[3 * 4] = {
            // Position        
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f,
        };
        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({ { ShaderDataType::Float3, "a_Position"} });
        m_SquareVA->AddVertexBuffer(squareVB);

        unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
        m_SquareVA->SetIndexBuffer(squareIB);

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

        std::string blueShaderVertexSrc = R"Src(
            #version 330 core

            layout(location=0) in vec3 a_Position;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }

        )Src";

        std::string blueShaderfragmentSrc = R"Src(
            #version 330 core

            layout(location=0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }

        )Src";

        m_BlueShader.reset(Shader::Create(blueShaderVertexSrc, blueShaderfragmentSrc));
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
            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_BlueShader->Bind();
            Renderer::Submit(m_SquareVA);
            
            m_Shader->Bind();
            Renderer::Submit(m_VertexArray);

            Renderer::EndScene();

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
