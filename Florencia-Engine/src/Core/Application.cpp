#include "Application.h"

namespace Florencia {

	Application::Application(const std::string& name, unsigned width, unsigned height) {
		m_Window = Window::Create({name, width, height});
	}

	Application::~Application() {
		delete m_Window;
	}

	void Application::Run() {
		while (m_Running) {
			
			m_Window->OnUpdate();
		}
	}

}