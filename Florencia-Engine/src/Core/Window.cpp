#include "Window.h"
#include "Platform/Platform.h"
#ifdef FLO_PLATFORM_WINDOWS
#include "Platform/Windows/Wwindow.h"
#elif defined(FLO_PLATFORM_WINDOWS_32)
#include "Platform/Windows/Wwindow.h"
#elif defined(FLO_PLATFORM_LINUX)
//#include "Platform/Linux/Window.h"
#endif

namespace Florencia {
	Window::Window() {
		//Create Console
		#ifdef _DEBUG
		m_Console = Console::Create();
		#endif
	}

	Window::~Window() {
		//Destroy Console
		#ifdef _DEBUG
		delete m_Console;
		#endif
	}

	Window* Window::Create(const WindowProps& props) {
		#ifdef FLO_PLATFORM_WINDOWS
		return new Wwindow(props);
		#endif
		#ifdef FLO_PLATFORM_WINDOWS_32
		return new Wwindow(props);
		#endif
		#ifdef FLO_PLATFORM_LINUX
		return nullptr;
		#endif
		#ifdef FLO_PLATFORM_MACOS
		return nullptr;
		#endif
	}
}