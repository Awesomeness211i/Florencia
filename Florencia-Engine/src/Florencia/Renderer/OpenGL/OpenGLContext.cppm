export module OpenGLContext;
import GraphicsContext;
import <GLFW/glfw3.h>;
import <glad/glad.h>;
import <iostream>;


export namespace Florencia {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(void* windowHandle, bool vsync);

		void Init() override;
		void SwapBuffers() override;
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
	private:
		void* m_WindowHandle;
		bool m_Vsync;
	};

}