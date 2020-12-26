#pragma once
#include <Core/Window.h>
#include <Core/LayerStack.h>
#include <Renderer/Renderer.h>

#define FLO_BIND_EVENT_FN(fn) [this](auto&&... args)->decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Florencia {

	class Application {
	public:
		Application(const std::string& name, unsigned width = 960, unsigned height = 540);
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Run();

	private:

		Window* m_Window;

		bool m_Running = true, m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}