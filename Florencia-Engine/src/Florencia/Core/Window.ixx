export module Window;
export import EventCallback;
import <stdint.h>;
import <string>;
import Event;

export namespace Florencia {

	struct WindowProps {
		WindowProps(const std::string& title, uint32_t width = 0, uint32_t height = 0) :Title(title), Width(width), Height(height) {}
		std::string Title;
		uint32_t Width, Height;
	};

	template <typename T>
	class Window {
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallback<T> function) = 0;

		//Window Attributes
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;

		virtual void* GetWindowHandle() = 0;
	};

}