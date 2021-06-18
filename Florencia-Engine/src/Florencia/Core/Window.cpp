module;
#include <Florencia/Core/PlatformDetection.h>
module Window;
import Wwindow;
import LinuxWindow;
import MacWindow;
import IPhoneWindow;
import AndroidWindow;

namespace Florencia {

	Window* Window::Create(const WindowProps& props) {
		#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
		return new Wwindow(props);
		#elif defined(FLO_PLATFORM_MACOS)
		return new MacWindow(props);
		#elif defined(FLO_PLATFORM_LINUX)
		return new LinuxWindow(props);
		#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
		return new IPhoneWindow(props);
		#elif defined(FLO_PLATFORM_ANDROID)
		return new AndroidWindow(props);
		#endif
		return nullptr;
	}

}