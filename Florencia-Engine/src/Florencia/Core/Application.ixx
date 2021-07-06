module;
#include <string>
export module Application;
import ApplicationEvent;
import GraphicsContext;
import LayerStack;
import Timestep;
import Renderer;
import Window;
import Layer;
import Event;

export namespace Florencia {

	class Application {
	public:
		Application(const WindowProps& props);

		virtual ~Application();

		void Run() {
			while (m_Running) {
				//time is in seconds
				m_LastTick = Time::GetCurrentTime();
				if (!m_Minimized) [[likely]] {
					if (m_Window) [[likely]] { m_Window->OnUpdate(); }
					Time time = Time::GetCurrentTime();
					Timestep ts(m_LastTick, time);
					m_LastTick = time;
					for (auto layer : m_LayerStack) {
						layer->Update(ts);
						layer->Render();
					}
					if (m_Context) [[likely]] { m_Context->SwapBuffers(); }
				}
			}
		}

		void OnEvent(Event& e) {
			EventHandler.Dispatch<WindowCloseEvent>(e, [this](WindowCloseEvent& e) -> bool { return this->Application::OnWindowClose(e); });
			EventHandler.Dispatch<WindowResizeEvent>(e, [this](WindowResizeEvent& e) -> bool { return this->Application::OnWindowResize(e); });

			for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
				if (e.Handled) break;
				(*it)->OnEvent(e);
			}
		}

		void AddLayer(Layer* layer) {
			m_LayerStack.AddLayer(layer);
			layer->OnAdd();
		}

		void AddOverlay(Layer* layer) {
			m_LayerStack.AddOverlay(layer);
			layer->OnAdd();
		}

		void RemoveLayer(Layer* layer) {
			m_LayerStack.RemoveLayer(layer);
			layer->OnRemove();
		}
		void RemoveOverlay(Layer* layer) {
			m_LayerStack.RemoveOverlay(layer);
			layer->OnRemove();
		}

		Window* GetWindow() { return m_Window; }

	private: //Functions
		bool OnWindowClose(WindowCloseEvent& e) {
			m_Running = false;
			return true;
		}

		bool OnWindowResize(WindowResizeEvent& e) {
			if (e.GetWidth() == 0 || e.GetHeight() == 0) [[unlikely]] { m_Minimized = true; }
			else [[likely]] { m_Minimized = false; Renderer::OnWindowResize(e.GetWidth(), e.GetHeight()); }
			return false;
		}

	private: //Variables
		LayerStack m_LayerStack;
		Window* m_Window = nullptr;
		GraphicsContext* m_Context = nullptr;
		Time m_LastTick{Time::GetCurrentTime()};
		bool m_Running = true, m_Minimized = false;
	};

	Application* CreateApplication();
}