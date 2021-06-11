export module Window;
import <functional>;
import <stdint.h>;
import Event;

export namespace Florencia {

	struct WindowProps {
		WindowProps(const std::string& title, uint32_t width = 0, uint32_t height = 0) :Title(title), Width(width), Height(height) {}
		std::string Title;
		uint32_t Width, Height;
	};

	class Window {
	public:
		enum class Platform {
			Windows,
			Android,
			IPhone,
			Linux,
			MacOS,
			None
		};
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		void SetEventCallback(const EventCallbackFn& Fn) { m_CallbackFunction = Fn; }

		//Window Attributes
		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;

		virtual void* GetWindowHandle() = 0;

		static Window* Create(const WindowProps& props);
	private:
		static Platform s_Platform;
	protected:
		EventCallbackFn m_CallbackFunction;
	};
}