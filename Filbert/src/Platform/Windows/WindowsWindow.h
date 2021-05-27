#pragma once

#include "Filbert/Window.h"
#include "Filbert/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


struct GLFWwindow;

namespace Filbert
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        // Window Attributes
        inline void SetEventCallback(const EventCallBackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return m_Window; }
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* m_Window;
        GraphicsContext* m_Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallBackFn EventCallback;
        };

        WindowData m_Data;
    };
}