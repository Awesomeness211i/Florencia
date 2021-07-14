module;
#include <Florencia/Core/PlatformDetection.h>
export module CreateFunctions.Window;
import WindowsWindow;
import LinuxWindow;
import Window;

export namespace Florencia {

	export Window* CreateWindow(const WindowProps& props) {
		#if defined(FLO_PLATFORM_WINDOWS_64)
		return new WindowsWindow(props);
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