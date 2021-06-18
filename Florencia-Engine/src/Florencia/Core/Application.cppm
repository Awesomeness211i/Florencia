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
			m_Console->CreateNewConsole();
			#endif

			//Create Window and Graphics Context
			m_Window = Window::Create(WindowProps(props));
			if (m_Window) {
				m_Window->SetEventCallback([this](Event& e) -> void { return this->Application::OnEvent(e); });
				m_Context = GraphicsContext::Create(m_Window);
				if (m_Context) {
					m_Context->Init();
				}
			}

			Renderer::Init();
		}

		virtual ~Application() {
			#if defined(FLO_DEBUG) || defined(FLO_RELEASE)
			m_Console->ReleaseConsole();
			delete m_Console;
			#endif
			delete m_Window;
		}

		void Run() {
			while (m_Running) {
				//time is in seconds
				m_LastTick = Clock::now();
				if (!m_Minimized) {
					if (m_Window) m_Window->OnUpdate();
					Time time = Clock::now();
					Timestep ts(m_LastTick, time);
					m_LastTick = time;
					for (auto layer : m_LayerStack) {
						layer->Update(ts);
					}
					if (m_Context) { m_Context->SwapBuffers(); }
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
		void RemoveLayer(Layer* layer) { m_LayerStack.RemoveLayer(layer); }
		void RemoveOverlay(Layer* layer) { m_LayerStack.RemoveOverlay(layer); }

		Window* GetWindow() { return m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e) { m_Running = false; return true; }
		bool OnWindowResize(WindowResizeEvent& e) {
			if (e.GetWidth() == 0 || e.GetHeight() == 0) { m_Minimized = true; }
			else {
				m_Minimized = false;
				Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
			}
			return false;
		}

		Window* m_Window;
		GraphicsContext* m_Context;

		LayerStack m_LayerStack;
		Time m_LastTick{Clock::now()};
		bool m_Running = true, m_Minimized = false;

		#if defined(FLO_DEBUG) || defined(FLO_RELEASE)
		Console* m_Console;
		#endif
	};

	Application* CreateApplication();
}