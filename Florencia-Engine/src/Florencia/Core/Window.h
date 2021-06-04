#pragma once
#include <stdint.h>
#include <functional>

namespace Florencia {

	struct WindowProps {
		WindowProps(const std::string& title, uint32_t width = 0, uint32_t height = 0) :Title(title), Width(width), Height(height) {}
		std::string Title;
		uint32_t Width, Height;
	};

	class Window {
	public:
		virtual ~Window() = default;

		virtual bool OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		//Window Attributes
		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;

		virtual void* GetWindowHandle() = 0;

		static Window* Create(const WindowProps& props);
	};
}
