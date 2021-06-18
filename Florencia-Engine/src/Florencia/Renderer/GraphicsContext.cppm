export module GraphicsContext;
import Renderer;

export namespace Florencia {

	class Window;

	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool enabled) = 0;

		static GraphicsContext* Create(Window* window, bool vsync = true);
	};

}