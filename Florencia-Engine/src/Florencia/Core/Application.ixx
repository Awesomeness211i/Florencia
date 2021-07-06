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

		void Run();

		void OnEvent(Event& e);

		void AddLayer(Layer* layer);

		void AddOverlay(Layer* layer);

		void RemoveLayer(Layer* layer);

		void RemoveOverlay(Layer* layer);

		Window* GetWindow() { return m_Window; }

	private:
		//Functions
		bool OnWindowClose(WindowCloseEvent& e);

		bool OnWindowResize(WindowResizeEvent& e);

		//Variables
		Time m_LastTick;
		LayerStack m_LayerStack;
		Window* m_Window = nullptr;
		GraphicsContext* m_Context = nullptr;
		bool m_Running = true, m_Minimized = false;
	};

	Application* CreateApplication();
}