module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
export module OpenGLContext;
import GraphicsContext;

export namespace Florencia {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(Window* handle, bool vsync) : m_Handle(handle), m_Vsync(vsync) {}

		void Init() override {
			glfwMakeContextCurrent(nullptr);
			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			if (!status) {}
		}

		void SwapBuffers() override {
			glfwSwapBuffers(nullptr);
		}

		bool IsVSync() const override {
			return m_Vsync;
		}

		void SetVSync(bool enabled) override {
			if (enabled) { glfwSwapInterval(1); }
			else { glfwSwapInterval(0); }
			m_Vsync = enabled;
		}

	private:
		Window* m_Handle;
		bool m_Vsync;
	};

}