export module MetalContext;
import GraphicsContext;

export namespace Florencia {

	class MetalContext : public GraphicsContext {
	public:
		MetalContext(Window* handle, bool vsync) : m_Handle(handle), m_Vsync(vsync) {}

		void Init() override {

		}

		void SwapBuffers() override {

		}

		bool IsVSync() const override {
			return false;
		}

		void SetVSync(bool enabled) override {

		}

	private:
		Window* m_Handle;
		bool m_Vsync;
	};

}