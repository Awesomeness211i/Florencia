#include "Application.h"

namespace Florencia {

	Application::Application(const std::string& name, unsigned width, unsigned height) {
		m_Window = Window::Create(WindowProps(name, width, height));
		m_Window->SetEventCallback(FLO_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {
		delete m_Window;
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(FLO_BIND_EVENT_FN(Application::OnAppClose));
		dispatcher.Dispatch<WindowResizeEvent>(FLO_BIND_EVENT_FN(Application::OnWindowResize));
	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}

	bool Application::OnAppClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		return false;
	}

}