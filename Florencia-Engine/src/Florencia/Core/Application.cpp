#include "Application.h"

#include <chrono>

namespace Florencia {

	Application::Application(const WindowProps& props) {
		m_Window = Window::Create(WindowProps(props));
		Renderer::Init();
	}

	Application::~Application() { delete m_Window; }

	void Application::Run() {
		while (m_Running) {
			
			float time = std::chrono::high_resolution_clock::now().time_since_epoch().count() * 1E-9;
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				for (auto layer : m_LayerStack) {
					layer->Update(ts);
					layer->Render();
				}
			}
			m_Running = m_Window->OnUpdate();
		}
	}

	void Application::AddLayer(Layer* layer) {
		m_LayerStack.AddLayer(layer);
		layer->OnAdd();
	}

	void Application::AddOverlay(Layer* layer) {
		m_LayerStack.AddOverlay(layer);
		layer->OnAdd();
	}

	void Application::RemoveLayer(Layer* layer) {
		m_LayerStack.RemoveLayer(layer);
	}

	void Application::RemoveOverlay(Layer* layer) {
		m_LayerStack.RemoveOverlay(layer);
	}

}