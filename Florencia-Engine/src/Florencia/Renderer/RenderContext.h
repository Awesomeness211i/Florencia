#pragma once
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Core/Window.h"

namespace Florencia {

	export class RenderContext {
	public:
		RenderContext(Window& window);
		~RenderContext();

		void Init(Window& window);

		void SwapBuffers();
	private:
		GLFWwindow* m_Window = nullptr;
	};

}

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