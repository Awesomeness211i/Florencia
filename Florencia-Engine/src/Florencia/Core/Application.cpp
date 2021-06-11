module;
#include <chrono>
module Application;

namespace Florencia {

	Application::Application(const WindowProps& props) {
		m_Window = Window::Create(WindowProps(props));
		if(m_Window) m_Window->SetEventCallback([this](Event& e) ->void { return this->Application::OnEvent(e); });
		Renderer::Init();
	}

	Application::~Application() { delete m_Window; }

	void Application::Run() {
		while (m_Running) {

			float time = (float)(std::chrono::high_resolution_clock::now().time_since_epoch().count() * 1E-9);
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				for (auto layer : m_LayerStack) {
					layer->Update(ts);
					layer->Render();
				}
			}
			if (m_Window) m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		m_EventHandler.Dispatch<WindowCloseEvent>(e, [this](WindowCloseEvent& e) -> bool { return this->Application::OnWindowClose(e); });
		m_EventHandler.Dispatch<WindowResizeEvent>(e, [this](WindowResizeEvent& e) -> bool { return this->Application::OnWindowResize(e); });

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (e.Handled) break;
			(*it)->OnEvent(e);
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

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) { m_Minimized = true; }
		else {
			m_Minimized = false;
			Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		}
		return false;
	}

}