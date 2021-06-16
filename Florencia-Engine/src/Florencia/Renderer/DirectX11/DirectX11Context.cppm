export module DirectX11Context;
import GraphicsContext;

export namespace Florencia {

	class DirectX11Context : public GraphicsContext {
	public:
		DirectX11Context(void* window, bool vsync);

		void Init() override;
		void SwapBuffers() override;
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
	private:
		void* m_WindowHandle;
		bool m_Vsync;
	};

}