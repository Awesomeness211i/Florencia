module Application;

namespace Florencia {

	Application::Application(const WindowProps& props) {
		m_Window = Window::Create(WindowProps(props));
		if (m_Window) [[likely]] {
			m_Window->SetEventCallback([this](Event& e) -> void { return this->Application::OnEvent(e); });
			m_Context = GraphicsContext::Create(m_Window);
			if (m_Context) [[likely]] { m_Context->Init(); }
		}

		Renderer::Init();
	}

	Application::~Application() {
		if (m_Context) [[likely]] { delete m_Context; }
		if (m_Window) [[likely]] { delete m_Window; }
	}

}