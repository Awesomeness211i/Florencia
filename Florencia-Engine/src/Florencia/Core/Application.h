#pragma once
#include <Core/Window.h>
#include <Renderer/Renderer.h>

namespace Florencia {

	struct ApplicationProps {
		ApplicationProps(const std::string& title = "", Uint32 width = 1080, Uint32 height = 720, bool vsync = true)
			: VSync(vsync), Title(title), Width(width), Height(height) {}
		bool VSync;
		std::string Title;
		Uint32 Width, Height;
	};

	class Application {
	public:
		Application(const ApplicationProps& props);
		virtual ~Application();
		Window* GetWindow() { return m_Window; }
		void Run();
	private:
		Window* m_Window;
		float m_LastFrameTime = 0.0f;
		bool m_Running = true, m_Minimized = false;
	};

	Application* CreateApplication();
}