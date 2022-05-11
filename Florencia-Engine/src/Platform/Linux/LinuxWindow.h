#pragma once
#include "../../Florencia/Core/PlatformDetection.h"
#if defined(FLO_PLATFORM_LINUX)
#include <stdint.h>
#include "GLFW/glfw3.h"
#include "../../Florencia/Core/Window.h"

namespace Florencia {

	class LinuxWindow final : public Window {
	public:
		LinuxWindow(const WindowProps& props);

		~LinuxWindow();

		void Update() override;

		void Render() override;

		WindowProps GetProperties() const override {
			return m_Properties;
		}

		void SetEventCallback(const EventCallback function) override { m_Properties.CallbackFunction = function; }

		uint32_t GetWidth() const override { return m_Properties.Width; }
		uint32_t GetHeight() const override { return m_Properties.Height; }

		//Window Attributes
		void SetWidth(uint32_t width) override {

		}
		void SetHeight(uint32_t height) override {
			
		}

		void* GetWindowHandle() const override { return m_Window; }
	private:
		WindowProps m_Properties;
		GLFWwindow* m_Window = nullptr;
	};

}
#endif