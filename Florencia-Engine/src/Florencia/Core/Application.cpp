#include "Application.h"

namespace Florencia {

	Application::Application(const WindowProps& props) {
		m_Window = Window::Create(WindowProps(props));
		Renderer::Init();
	}

	Application::~Application() { delete m_Window; }

	void Application::Run() {
		while (m_Running) {
			if (m_Window->IsVSync()) {

			}
			m_Running = m_Window->OnUpdate();
		}
	}

}