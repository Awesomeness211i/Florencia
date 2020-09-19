#pragma once
#include <string>
#include <Core/Console.h>

namespace Florencia {

	struct WindowProps {
		std::string name;
		unsigned width, height;
	};

	class Window {
	public:
		Window();
		virtual ~Window();
		virtual void OnUpdate() = 0;
		static Window* Create(const WindowProps& props);
	#ifdef _DEBUG
	private:
		Console* m_Console;
	#endif
	};
}