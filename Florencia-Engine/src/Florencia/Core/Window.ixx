module;
#include <stdint.h>
#include <functional>
export module Window;
export import <string>;
import Event;

export namespace Florencia {

	struct WindowProps {
		WindowProps(const std::string& title, uint32_t width = 0, uint32_t height = 0) :Title(title), Width(width), Height(height) {}
		std::string Title;
		uint32_t Width, Height;
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		void SetEventCallback(const EventCallbackFn& function) { m_CallbackFunction = function; }

		//Window Attributes
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;

		virtual void* GetWindowHandle() = 0;

		static Window* Create(const WindowProps& props);
	protected:
		EventCallbackFn m_CallbackFunction;
	};
}