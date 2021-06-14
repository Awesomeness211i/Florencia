module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
module OpenGLContext;

namespace Florencia {

	OpenGLContext::OpenGLContext(void* window, bool vsync) : m_WindowHandle(window), m_Vsync(vsync) {}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(nullptr);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status) {}
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