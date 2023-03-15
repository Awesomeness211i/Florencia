#include "Application.h"
#include "Window.h"
#include "Layer.h"

#include "Florencia/Events/Event.h"

#include <stdexcept>
#include <filesystem>
#include <string_view>

namespace Florencia {

	const char* ApplicationCommandLineArgs::operator[](int index) const { return (*Args).string().c_str(); }

	const char* ApplicationCommandLineArgs::at(int index) const {
		if (index < Count) { return (*Args).string().c_str(); }
		throw std::runtime_error("Index not within bounds");
	}

	Application::Application(std::string_view name, ApplicationCommandLineArgs args) {
		m_CommandLineArgs = args;
		m_Window = new Window(WindowProps(name, 1080, 720));
		if(m_Window) [[likely]] {
			m_Window->SetEventCallback([this](Event& e) -> void { return Application::OnEvent(e); });
			//m_Renderer = new Renderer(*m_RenderContext);
		}
	}

	Application::~Application() {
		if(m_Window) [[likely]] {
			//delete m_Renderer;
			delete m_Window;
		}
	}

	void Application::Run() {
		while (m_Running) {
			//time is in seconds
			m_LastTick = TimePoint();
			if(!m_Minimized) [[likely]] {
				if(m_Window) [[likely]] { m_Window->Update(); }
				TimePoint nextTime = TimePoint();
				TimeStep ts(m_LastTick, nextTime);
				for (Layer* layer : m_LayerStack) {
					layer->Update(ts);
					layer->Render();
				}
				if(m_Window) [[likely]] { m_Window->Render(); }
				m_LastTick = nextTime;
			}
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher EventHandler;
		EventHandler.Dispatch<WindowCloseEvent>(e, [this](WindowCloseEvent& e) -> bool { return OnWindowClose(e); });
		EventHandler.Dispatch<WindowResizeEvent>(e, [this](WindowResizeEvent& e) -> bool { return OnWindowResize(e); });

		for (std::vector<Layer*>::reverse_iterator it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
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
		layer->OnRemove();
	}

	void Application::RemoveOverlay(Layer* layer) {
		m_LayerStack.RemoveOverlay(layer);
		layer->OnRemove();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) [[unlikely]] { m_Minimized = true; }
		else [[likely]] { m_Minimized = false; /*Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());*/ }
		return false;
	}

}
