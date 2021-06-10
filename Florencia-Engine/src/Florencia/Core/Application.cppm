export module Application;
import Event.Application;
import Event.Mouse;
import Event.Key;
import Event;

import LayerStack;
import Renderer;
import Window;
import Layer;

export namespace Florencia {

	class Application {
	public:
		Application(const WindowProps& props);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void AddLayer(Layer* layer);
		void AddOverlay(Layer* layer);
		void RemoveLayer(Layer* layer);
		void RemoveOverlay(Layer* layer);

		Window* GetWindow() { return m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Window* m_Window;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		bool m_Running = true, m_Minimized = false;

	protected:
		EventDispatcher m_EventHandler;
	};

	Application* CreateApplication();
}