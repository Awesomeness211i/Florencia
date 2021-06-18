export module IPhoneWindow;
import IPhoneConsole;
import Window;

export namespace Florencia {

	class IPhoneWindow : public Window {
	public:
		IPhoneWindow(const WindowProps& props) {}
		~IPhoneWindow() {}

		void OnUpdate() override {}

		uint32_t GetWidth() const override { return 0; }
		uint32_t GetHeight() const override { return 0; }

		//Window Attributes
		void SetWidth(uint32_t width) override {}
		void SetHeight(uint32_t height) override {}

		void* GetWindowHandle() override { return nullptr; }
	private:
		IPhoneConsole* m_Console;
	};

}