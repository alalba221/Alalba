#pragma once
#include "Base.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Alalba/ImGui/ImGuiLayer.h"
namespace Alalba{
  class ALALBA_API Application{
    
  public:
		Application();
		virtual ~Application();

		void Run();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate() {}

		virtual void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* overlayer);
		virtual void RenderImGui();

		std::string OpenFile(const std::string& filter) const;

		inline Window& GetWindow() { return *m_Window; }
		
		static inline Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		static Application* s_Instance;

  };
  Application *CreateApplication();
}