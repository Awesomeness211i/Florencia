export module MacWindow;
import MacConsole;
import Window;

export namespace Florencia {

	class MacWindow : public Window {
	public:
		MacWindow(const WindowProps& props) {}
		~MacWindow() {}

		void OnUpdate() override {}

		uint32_t GetWidth() const override { return 0; }
		uint32_t GetHeight() const override { return 0; }

		//Window Attributes
		void SetWidth(uint32_t width) override {}
		void SetHeight(uint32_t height) override {}

		void* GetWindowHandle() override { return nullptr; }
	private:
		MacConsole* m_Console;
	};

}