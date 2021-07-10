#pragma once
#include <Florencia/Core/PlatformDetection.h>

extern Florencia::Application* Florencia::CreateApplication(ApplicationCommandLineArgs args);

#if defined(FLO_PLATFORM_WINDOWS_64)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	auto app = Florencia::CreateApplication({ nCmdShow, (char**)lpCmdLine });
	app->Run();
	delete app;
	return 0;
}
#elif defined(FLO_PLATFORM_LINUX)
int main(int argc, char** argv) {
	auto app = Florencia::CreateApplication({ argc, argv });
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