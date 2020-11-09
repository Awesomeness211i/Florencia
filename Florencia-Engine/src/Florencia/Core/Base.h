#pragma once
//Write any needed code for General use

//Include any platform specific code
#include <Platform/Platform.h>
#if defined(WINDOW)
	#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
	#include <Platform/Windows/Wwindow.h>
	#elif defined(FLO_PLATFORM_LINUX)
	#include <Platform/Linux/LinuxWindow.h>
	#elif defined(FLO_PLATFORM_MACOS)
	#include <Platform/MacOS/MacWindow.h>
	#endif
#elif defined(NO)

#endif