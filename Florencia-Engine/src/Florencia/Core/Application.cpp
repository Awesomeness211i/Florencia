#include "Application.h"

namespace Florencia {

	Application::Application(const std::string& name, unsigned width, unsigned height) {
		m_Window = Window::Create(WindowProps(name, width, height));
		m_Window->SetEventCallback(FLO_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init(m_Window->GetWindowHandle());
	}

	Application::~Application() {
		Renderer::Shutdown();
		delete m_Window;
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(FLO_BIND_EVENT_FN(Application::OnAppClose));
		dispatcher.Dispatch<WindowResizeEvent>(FLO_BIND_EVENT_FN(Application::OnWindowResize));
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run() {
		while (m_Running) {
			if (m_Window->IsVSync()) {

			}
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