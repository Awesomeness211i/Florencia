#pragma once
#include <filesystem>

#include "Window.h"
#include "TimeStep.h"
#include "LayerStack.h"
#include "Florencia/Renderer/Renderer.h"
#include "Florencia/Events/ApplicationEvent.h"

namespace Florencia {

	struct ApplicationCommandLineArgs {
		int Count = 0;
		std::filesystem::path* Args = nullptr;

		const char* operator[](int index) const;
		const char* at(int index) const;
	};

	class Application {
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
		Renderer* m_Renderer{ nullptr };
		bool m_Running{ true }, m_Minimized{ false };
		ApplicationCommandLineArgs m_CommandLineArgs{};
	};

	Application* CreateApplication(ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
}