module;
#include <GLFW/glfw3.h>
#include <Florencia/Core/PlatformDetection.h>
export module AttachToWindowHandle;
import WindowsWindow;
import Window;

export namespace Florencia {

	//Converts to GLFWwindow* but returns as void*
	GLFWwindow* AttachToWindowHandle(const Window& handle, GLFWwindow* share) {
		#if defined(FLO_PLATFORM_WINDOWS_64)
		//return (GLFWwindow*)handle.GetWindowHandle();
		#elif defined(FLO_PLATFORM_LINUX)
		return;
		#elif defined(FLO_PLATFORM_MACOS)
		return;
		#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
		return;
		#elif defined(FLO_PLATFORM_ANDROID)
		return;
		#else
		return (GLFWwindow*)handle.GetWindowHandle();
		#endif
		return nullptr;
	}

}