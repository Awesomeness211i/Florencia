#pragma once
#include <Core/Application.h>
#include <Platform/Platform.h>

#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
	#include <Windows.h>
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#elif defined(FLO_PLATFORM_LINUX)
	int main(int argc, char** argv) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#elif defined(FLO_PLATFORM_MACOS)
	int main(int argc, char** argv) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#elif defined(FLO_PLATFORM_IPHONE)
	int main(int argc, char** argv) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#elif defined(FLO_PLATFORM_IPHONE_SIMULATOR)
	int main(int argc, char** argv) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#elif defined(FLO_PLATFORM_ANDROID)
	int main(int argc, char** argv) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
	}
#endif