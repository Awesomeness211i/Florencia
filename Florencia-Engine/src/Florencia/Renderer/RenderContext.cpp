#include "RenderContext.h"

namespace Florencia {

	RenderContext::RenderContext(Window& window) { Init(window); }

	RenderContext::~RenderContext() { /*glfwDestroyWindow(m_Window); glfwTerminate();*/ }

	void RenderContext::Init(Window& window) {
		/*if(!glfwInit()) {
			return;
		}
		m_Window = AttachToWindowHandle(window, nullptr);
		if(!m_Window) { glfwTerminate(); return; }

		glfwMakeContextCurrent(m_Window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSwapInterval(1);*/
	}

	void RenderContext::SwapBuffers() { /*glfwSwapBuffers(m_Window);*/ }

}
