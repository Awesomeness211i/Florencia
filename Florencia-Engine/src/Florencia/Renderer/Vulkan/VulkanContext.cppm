export module VulkanContext;
import GraphicsContext;

export namespace Florencia {

	class VulkanContext : public GraphicsContext {
	public:
		VulkanContext(void* windowHandle, bool vsync);

		void Init() override;
		void SwapBuffers() override;
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
	private:
		void* m_WindowHandle;
		bool m_Vsync;
	};

}