#include "Application.h"

namespace Florencia {

	Application::Application(const WindowProps& props) {
		m_Window = Window::Create(props);
	}

	Application::~Application() {
		delete m_Window;
	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnRender();
			m_Running = m_Window->OnUpdate();
		}
	}

}