#pragma once
#include <Florencia/Renderer/GraphicsContext.h>

struct GLFWwindow;

namespace Florencia {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle, bool vsync = true);

		void Init() override;
		void SwapBuffers() override;
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
	private:
		GLFWwindow* m_WindowHandle;
		bool m_Vsync;
	};

}