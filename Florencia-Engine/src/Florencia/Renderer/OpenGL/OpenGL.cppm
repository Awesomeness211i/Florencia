module;
#include <stdint.h>
#include <glad/glad.h>
#include <Florencia/Core/PlatformDetection.h>
export module OpenGL;
import RendererAPI;

export namespace Florencia {

	void OpenGLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH: /*LOG(message);*/ return;
			case GL_DEBUG_SEVERITY_MEDIUM: /*LOG(message);*/ return;
			case GL_DEBUG_SEVERITY_LOW: /*LOG(message);*/ return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: /*LOG(message);*/ return;
		}
	}

	class OpenGL : public RendererAPI {
	public:
		OpenGL() {}

		void Init() override {
			#if defined(FLO_DEBUG) || defined(FLO_RELEASE)
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			#if defined(FLO_PLATFORM_WINDOWS_64)
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);
			#endif

			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
			#endif

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
		}

		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override {
			glViewport(x, y, width, height);
		}

		void SetClearColor(const FloMath::Vec4<float>& color) override {
			glClearColor(color[0], color[1], color[2], color[3]);
		}

		void Clear() override {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		/*void DrawIndexed(const VertexArray& vertexArray, uint32_t indexCount) {
			uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
			glBindTexture(GL_TEXTURE_2D, 0);
		}*/

	};

}