#pragma once
#include <Florencia/Renderer/GraphicsContext.h>

struct GLFWwindow;

namespace Florencia {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}