module;
#include <stdexcept>
#include <filesystem>
#include <string_view>
export module Application;
import ApplicationEvent;
import LayerStack;
import TimeStep;
import Renderer;
import Console;
import Window;
import Layer;
import Event;

namespace Florencia {

	export struct ApplicationCommandLineArgs {
		int Count = 0;
		std::filesystem::path* Args = nullptr;

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
		
		Window* GetWindow() { return m_Window; }
	private:
		//Functions
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		//Variables
		TimePoint m_LastTick;
		LayerStack m_LayerStack;
		Window* m_Window{ nullptr };
		Console* m_Console{ nullptr };
		Renderer* m_Renderer{ nullptr };
		bool m_Running{ true }, m_Minimized{ false };
		ApplicationCommandLineArgs m_CommandLineArgs{};
	};

	export Application* CreateApplication(ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
}

module: private;
import CreateFunctions.Console;
import CreateFunctions.Window;

namespace Florencia {

	const char* ApplicationCommandLineArgs::operator[](int index) const { return (*Args).string().c_str(); }

	const char* ApplicationCommandLineArgs::at(int index) const {
		if (index < Count) { return (*Args).string().c_str(); }
		throw std::runtime_error("Index not within bounds");
	}

	Application::Application(std::string_view name, ApplicationCommandLineArgs args) {
		m_CommandLineArgs = args;
		//m_Console = CreateConsole();
		//m_Window = CreateWindow(WindowProps(name, 1080, 720));
		if(m_Window) [[likely]] {
			m_Window->SetEventCallback([this](Event& e) -> void { return Application::OnEvent(e); });
			//m_Renderer = new Renderer(*m_RenderContext);
		}
	}

	Application::~Application() {
		if(m_Window) [[likely]] {
			delete m_Renderer;
			delete m_Window;
		}
		if (m_Console) [[likely]] { m_Console->ReleaseConsole(); delete m_Console; }
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