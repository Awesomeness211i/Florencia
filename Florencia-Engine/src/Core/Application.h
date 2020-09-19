#pragma once
#include <Core/Window.h>

namespace Florencia {

	class Application {
	public:
		Application(const std::string& name, unsigned width = 960, unsigned height = 540);
		virtual ~Application();

		void Run();

	private:
		bool m_Running = true;
		Window* m_Window;
	};

	//To be implemented in client
	Application* CreateApplication();
}