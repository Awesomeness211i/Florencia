#pragma once
#include <string>
#include <Core/Console.h>

namespace Florencia {

	struct WindowProps {
		WindowProps(const std::string& title, unsigned width, unsigned height)
			: m_Name(title), m_Width(width), m_Height(height) {}
		std::string m_Name;
		unsigned m_Width, m_Height;
	};

	class Window {
	public:
		Window();
		virtual ~Window();
		virtual void OnUpdate() = 0;
		virtual void* GetWindowHandle() = 0;
		static Window* Create(const WindowProps& props);
	private:
	#ifdef _DEBUG
		Console* m_Console;
	#endif
	};
}