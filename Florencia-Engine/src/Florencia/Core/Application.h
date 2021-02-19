#pragma once
#include "Window.h"

namespace Florencia {

	class Application {
	public:
		Application(const WindowProps& props);
		virtual ~Application();
		Window* GetWindow() { return m_Window; }
		void Run();
	private:
		Window* m_Window;
		float m_LastFrameTime = 0.0f;
		bool m_Running = true, m_Minimized = false;
	};

	Application* CreateApplication();
}