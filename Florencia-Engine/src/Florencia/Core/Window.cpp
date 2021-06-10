module;
#include <Florencia/Core/PlatformDetection.h>
module Window;
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
import Wwindow;
#elif defined(FLO_PLATFORM_LINUX)
//#include <Platform/Linux/LinuxWindow.h>
#elif defined(FLO_PLATFORM_ANDROID)
//#include <Platform/Android/AndroidWindow.h>
#elif defined(FLO_PLATFORM_MACOS)
//#include <Platform/MacOS/MacWindow.h>
#endif

namespace Florencia {

	Window* Window::Create(const WindowProps& props) {
		#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
		return new Wwindow(props);
		#elif defined(FLO_PLATFORM_LINUX)
		return nullptr;
		#elif defined(FLO_PLATFORM_ANDROID)
		return nullptr;
		#elif defined(FLO_PLATFORM_MACOS)
		return nullptr;
		#elif defined(FLO_PLATFORM_IPHONE)
		return nullptr;
		#else
		return nullptr;
		#endif
	}
}
