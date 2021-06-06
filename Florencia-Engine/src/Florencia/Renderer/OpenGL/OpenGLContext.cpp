#include "OpenGLContext.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Florencia {

	OpenGLContext::OpenGLContext(void* window, bool vsync) : m_WindowHandle(window), m_Vsync(vsync) {}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(nullptr);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status) { std::cout << "failed to load glad!\n"; }
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(nullptr);
	}

	bool OpenGLContext::IsVSync() const {
		return m_Vsync;
	}

	void OpenGLContext::SetVSync(bool enabled) {
		if (enabled) { glfwSwapInterval(1); }
		else { glfwSwapInterval(0); }
		m_Vsync = enabled;
	}

}