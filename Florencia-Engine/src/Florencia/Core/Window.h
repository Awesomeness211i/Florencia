#pragma once
#include <stdint.h>
#include <functional>
#include <string_view>

#include "Florencia/Events/Event.h"

struct GLFWwindow;

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
		Window(const WindowProps& props);
		~Window();

		void Update();
		void Render();
		uint32_t GetWidth() const { return m_Properties.Width; }
		uint32_t GetHeight() const { return m_Properties.Height; }
		WindowProps GetProperties() const { return m_Properties; }
		void SetEventCallback(const EventCallback function) { m_Properties.CallbackFunction = function; }

		//Window Attributes
		void SetWidth(uint32_t width) { m_Properties.Width = width; }
		void SetHeight(uint32_t height) { m_Properties.Height = height; };

		void* GetWindowHandle() const { return m_Window; };
	private:
		GLFWwindow* m_Window{ nullptr };
		WindowProps m_Properties;
	};

}