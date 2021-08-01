export module LinuxWindow;
import <stdint.h>;
import Window;

export namespace Florencia {

	class LinuxWindow final : public Window {
	public:
		LinuxWindow(const WindowProps& props) {

		}

		~LinuxWindow() {

		}

		void Update() override {

		}

		void SetEventCallback(const EventCallback function) override { m_CallbackFunction = function; }

		uint32_t GetWidth() const override { return 0; }
		uint32_t GetHeight() const override { return 0; }

		//Window Attributes
		void SetWidth(uint32_t width) override {}
		void SetHeight(uint32_t height) override {}

		void* GetWindowHandle() const override { return nullptr; }
	private:
		EventCallback m_CallbackFunction;
	};

}