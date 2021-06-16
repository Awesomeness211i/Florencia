export module MacWindow;
import Window;

export namespace Florencia {

	class MacWindow : public Window {
	public:
		MacWindow(const WindowProps& props);
		~MacWindow();

		void OnUpdate() override;

		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;

		//Window Attributes
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
		void SetWidth(uint32_t width) override;
		void SetHeight(uint32_t height) override;

		void* GetWindowHandle() override;
	private:

	};

}