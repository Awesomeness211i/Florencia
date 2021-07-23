export module Application;
import CreateFunctions.Console;
import CreateFunctions.Window;
import ApplicationEvent;
import LayerStack;
import TimeStep;

import <string>;

namespace Florencia {

	export struct ApplicationCommandLineArgs {
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const;
		const char* at(int index) const;
	};

	export class Application {
	public:
		Application(std::string_view name, ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void AddLayer(Layer* layer);
		void AddOverlay(Layer* layer);

		void RemoveLayer(Layer* layer);
		void RemoveOverlay(Layer* layer);

		Window<Application>* GetWindow() { return m_Window; }
	private:
		//Functions
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		//Variables
		TimePoint m_LastTick;
		LayerStack m_LayerStack;
		bool m_Running = true, m_Minimized = false;

		Console* m_Console = nullptr;
		Window<Application>* m_Window = nullptr;
	};

	export Application* CreateApplication(ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
}

module: private;
import EventCallback;

import <stdexcept>;

namespace Florencia {

	const char* ApplicationCommandLineArgs::operator[](int index) const {
		return Args[index];
	}

	const char* ApplicationCommandLineArgs::at(int index) const {
		if (index < Count) { return Args[index]; }
		throw std::runtime_error("Index not within bounds");
	}

	void Callback(Application* app, Event& e) { return app->OnEvent(e); }

	Application::Application(std::string_view name, ApplicationCommandLineArgs args) {
		#ifdef FLO_DEBUG
		m_Console = CreateConsole();
		#endif
		m_Window = CreateWindow<Application>(WindowProps(name, 1080, 720));
		if (m_Window) [[likely]] { m_Window->SetEventCallback(EventCallback<Application>(this, Callback)); }
	}

	Application::~Application() {
		if (m_Window) [[likely]] { delete m_Window; }
		if (m_Console) [[likely]] { m_Console->ReleaseConsole(); delete m_Console; }
	}

	void Application::Run() {
		while (m_Running) {
			//time is in seconds
			m_LastTick = TimePoint();
			if (!m_Minimized) [[likely]] {
				if (m_Window) [[likely]] { m_Window->Update(); }
				TimePoint nextTime = TimePoint();
				TimeStep ts(m_LastTick, nextTime);
				for (Layer* layer : m_LayerStack) {
					layer->Update(ts);
					layer->Render();
				}
				if (m_Window) [[likely]] { m_Window->Render(); }

				m_LastTick = nextTime;
			}
		}
	}

	void Application::OnEvent(Event& e) {
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