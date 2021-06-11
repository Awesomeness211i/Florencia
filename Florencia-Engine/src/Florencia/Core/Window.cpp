module;
#include <Florencia/Core/PlatformDetection.h>
module Window;
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
//import Wwindow;
#elif defined(FLO_PLATFORM_LINUX)
import LinuxWindow;
#elif defined(FLO_PLATFORM_ANDROID)
import AndroidWindow;
#elif defined(FLO_PLATFORM_IPHONE)
import IPhoneWindow;
#elif defined(FLO_PLATFORM_MACOS)
import MacWindow;
#endif

namespace Florencia {

	Window* Window::Create(const WindowProps& props) {
		#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
		//return new Wwindow(props);
		#elif defined(FLO_PLATFORM_LINUX)
		return new LinuxWindow(props);
		#elif defined(FLO_PLATFORM_ANDROID)
		return new AndroidWindow(props);
		#elif defined(FLO_PLATFORM_MACOS)
		return new MacWindow(props);
		#else defined(FLO_PLATFORM_IPHONE)
		return new IPhoneWindow(props);
		#endif
		return nullptr;
	}
}
