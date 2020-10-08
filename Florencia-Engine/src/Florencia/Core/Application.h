#pragma once
#include <Events/AppEvent.h>
#include <Core/Window.h>

#define FLO_BIND_EVENT_FN(fn) [this](auto&&... args)->decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Florencia {

	class Application {
	public:
		Application(const std::string& name, unsigned width = 960, unsigned height = 540);
		virtual ~Application();

		void OnEvent(Event& e);
		Window& GetWindow() { return *m_Window; }

		void Run();

	private:
		bool OnAppClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		bool m_Running = true;
		Window* m_Window;
	};

	//To be implemented in client
	Application* CreateApplication();
}