#include "Window.h"
#include <Core/Base.h>

namespace Florencia {

	Window* Window::Create(const WindowProps& props) {
		#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
		return new Wwindow(props);
		#elif defined(FLO_PLATFORM_LINUX)
		return nullptr;
		#elif defined(FLO_PLATFORM_MACOS)
		return nullptr;
		#endif
	}
}