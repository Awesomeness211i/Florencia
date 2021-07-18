export module LinuxWindow;
import <stdint.h>;
import Window;

export namespace Florencia {

	template<typename T>
	class LinuxWindow final : public Window<T> {
	public:
		LinuxWindow(const WindowProps& props) {

		}

		~LinuxWindow() {

		}

		void Update() override {

		}

		void SetEventCallback(const EventCallback<T> function) override { m_CallbackFunction = function; }

		uint32_t GetWidth() const override { return 0; }
		uint32_t GetHeight() const override { return 0; }

		//Window Attributes
		void SetWidth(uint32_t width) override {}
		void SetHeight(uint32_t height) override {}

		void* GetWindowHandle() override { return nullptr; }
	private:
		EventCallback<T> m_CallbackFunction;
	};

}