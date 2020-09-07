#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
	#ifdef _WIN64
		#define FLO_PLATFORM_WINDOWS
	#else
		#define FLO_PLATFORM_WINDOWS
		#error "x86 Builds aren't supported"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#define FLO_PLATFORM_IPHONE_SIMULATOR
		#error "IOS simulator is not supported"
	#elif TARGET_OS_IPHONE == 1
		#define FLO_PLATFORM_IPHONE
		#error "IOS is not supported"
	#elif TARGET_OS_MAC == 1
		#define FLO_PLATFORM_MACOS
		#error "MAC OS is not supported"
	#else
		#define FLO_Undefined_Platform
		#error "Unknown Apple platform"
	#endif
#elif defined(__ANDROID__)
	#define FLO_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define FLO_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#define FLO_Undefined_Platform
	#error "Unknown platform!"
#endif
#endif