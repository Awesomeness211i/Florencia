module;
#include <string>
#include <stdexcept>
export module Application;
import ApplicationEvent;
import EventCallback;
import LayerStack;
import Timestep;
import Window;
import Layer;
import Event;

namespace Florencia {

	export struct ApplicationCommandLineArgs {
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const {
			return Args[index];
		}

		const char* at(int index) const {
			if (index < Count) { return Args[index]; }
			throw std::runtime_error("Index not within bounds");
		}
	};

	export class Application {
	public:
		Application(const std::string& name, ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
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
		bool m_Running = true, m_Minimized = false;

		Window* m_Window;
	};

	export Application* CreateApplication(ApplicationCommandLineArgs args);
}