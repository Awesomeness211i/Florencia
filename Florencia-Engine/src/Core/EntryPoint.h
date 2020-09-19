#pragma once
#include "Platform/Platform.h"
#include "Application.h"

#ifdef FLO_PLATFORM_WINDOWS
	#include <Windows.h>
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#endif

#ifdef FLO_PLATFORM_WINDOWS_32
	#include <Windows.h>
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#endif

#ifdef FLO_PLATFORM_LINUX
	int main(int argc, char** argv) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#endif

#ifdef FLO_PLATFORM_MACOS
	int main(int argc, char** argv) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#endif

#ifdef FLO_PLATFORM_IPHONE
	
#endif

#ifdef FLO_PLATFORM_IPHONE_SIMULATOR
	
#endif

#ifdef FLO_PLATFORM_ANDROID
	
#endif