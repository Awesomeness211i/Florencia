#include "Application.h"

namespace Florencia {

	Application::Application(const std::string& name, unsigned width, unsigned height) {
		m_Window = Window::Create(WindowProps(name, width, height));

		Renderer::Init(m_Window->GetWindowHandle());
	}

	Application::~Application() {
		Renderer::Shutdown();
		delete m_Window;
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
			for (auto layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Running = m_Window->OnUpdate();
		}
	}

}