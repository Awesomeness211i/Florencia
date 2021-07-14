module;
#include <stdint.h>
#include <functional>
export module Window;
export import <string>;
import EventCallback;
import Event;

export namespace Florencia {

	class Application;

	struct WindowProps {
		WindowProps(const std::string& title, uint32_t width = 0, uint32_t height = 0) :Title(title), Width(width), Height(height) {}
		std::string Title;
		uint32_t Width, Height;
	};

	class Window {
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		void SetEventCallback(const EventCallback<Application> function);

		//Window Attributes
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;

		virtual void* GetWindowHandle() = 0;
	protected:
		EventCallback<Application> m_CallbackFunction;
	};
}

module: private;

namespace Florencia {

	void Window::SetEventCallback(const EventCallback<Application> function) {
		m_CallbackFunction = function;
	}

}