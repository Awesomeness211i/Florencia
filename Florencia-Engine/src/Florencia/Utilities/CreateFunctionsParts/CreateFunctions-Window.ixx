export module CreateFunctions.Window;
import <Florencia/Core/PlatformDetection.h>;
import WindowsWindow;
import LinuxWindow;
import Window;

export namespace Florencia {

	export template<typename T> Window<T>* CreateWindow(const WindowProps& props) {
		#if defined(FLO_PLATFORM_WINDOWS_64)
		return new WindowsWindow<T>(props);
		#elif defined(FLO_PLATFORM_MACOS)
		return new MacWindow<T>(props);
		#elif defined(FLO_PLATFORM_LINUX)
		return new LinuxWindow<T>(props);
		#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
		return new IPhoneWindow<T>(props);
		#elif defined(FLO_PLATFORM_ANDROID)
		return new AndroidWindow<T>(props);
		#endif
		return nullptr;
	}

}