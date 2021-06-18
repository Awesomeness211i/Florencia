export module Application;
import Event.Application;
import GraphicsContext;
import LayerStack;
import Timestep;
import Renderer;
import Console;
import Window;
import Layer;
import Event;

export namespace Florencia {

	class Application {
	public:
		Application(const WindowProps& props) {
			//Create Console
			#if defined(FLO_DEBUG) || defined(FLO_RELEASE)
			m_Console = Console::Create();
			#endif
			if (m_Console) [[likely]] { m_Console->CreateNewConsole(); }

			//Create Window and Graphics Context
			m_Window = Window::Create(WindowProps(props));
			if (m_Window) [[likely]] {
				m_Window->SetEventCallback([this](Event& e) -> void { return this->Application::OnEvent(e); });
				m_Context = GraphicsContext::Create(m_Window);
				if (m_Context) [[likely]] { m_Context->Init(); }
			}

			Renderer::Init();
		}

		virtual ~Application() {
			#if defined(FLO_DEBUG) || defined(FLO_RELEASE)
			m_Console->ReleaseConsole();
			#endif
			if (m_Context) [[likely]] { delete m_Context; }
			if (m_Console) [[likely]] { delete m_Console; }
			if (m_Window) [[likely]] { delete m_Window; }
		}

		void Run() {
			while (m_Running) {
				//time is in seconds
				m_LastTick = Time::GetCurrentTime();
				if (!m_Minimized) [[unlikely]] {
					if (m_Window) m_Window->OnUpdate();
					Time time = Time::GetCurrentTime();
					Timestep ts(m_LastTick, time);
					m_LastTick = time;
					for (auto layer : m_LayerStack) { [[likely]] layer->Update(ts); }
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

	private:
		bool OnWindowClose(WindowCloseEvent& e) { m_Running = false; return true; }
		bool OnWindowResize(WindowResizeEvent& e) {
			if (e.GetWidth() == 0 || e.GetHeight() == 0) [[unlikely]] {
				m_Minimized = true;
			}
			else [[likely]] {
				m_Minimized = false;
				Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
			}
			return false;
		}

		Window* m_Window = nullptr;
		Console* m_Console = nullptr;
		GraphicsContext* m_Context = nullptr;

		LayerStack m_LayerStack;
		Time m_LastTick{Time::GetCurrentTime()};
		bool m_Running = true, m_Minimized = false;
	};

	Application* CreateApplication();
}