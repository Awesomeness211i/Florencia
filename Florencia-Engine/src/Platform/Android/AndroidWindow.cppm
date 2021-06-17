export module AndroidWindow;
import AndroidConsole;
import Window;

export namespace Florencia {

	class AndroidWindow : public Window {
	public:
		AndroidWindow(const WindowProps& props) {}
		~AndroidWindow() {}

		void OnUpdate() override {}

		uint32_t GetWidth() const override { return 0; }
		uint32_t GetHeight() const override { return 0; }

		//Window Attributes
		bool IsVSync() const override { return false; }
		void SetVSync(bool enabled) override {}
		void SetWidth(uint32_t width) override {}
		void SetHeight(uint32_t height) override {}

		void* GetWindowHandle() override { return nullptr; }
	private:
		AndroidConsole* m_Console;
	};

}