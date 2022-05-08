#pragma once
#include <stdint.h>
#include <functional>
#include <string_view>
#include "../Events/Event.h"

namespace Florencia {

	using EventCallback = std::function<void(Event&)>;

	struct WindowProps {
		WindowProps(std::string_view title, uint32_t width = 0, uint32_t height = 0) :Title(title), Width(width), Height(height) {}
		std::string_view Title;
		uint32_t Width, Height;
		EventCallback CallbackFunction;
	};

	class Window {
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual WindowProps GetProperties() const = 0;

		virtual void SetEventCallback(const EventCallback function) = 0;

		//Window Attributes
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;

		virtual void* GetWindowHandle() const = 0;
	};

}