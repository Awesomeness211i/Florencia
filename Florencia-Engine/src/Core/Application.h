#pragma once

namespace Florencia {

	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		bool m_Running = true;
	};

	//To be implemented in client
	Application* CreateApplication();
}