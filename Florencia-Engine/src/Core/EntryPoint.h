#pragma once
#include "Platform/Platform.h"
#include "Application.h"

#ifdef FLO_PLATFORM_WINDOWS
	int main(int argc, char** argv) {
		auto app = Florencia::CreateApplication();
		app->Run();
		delete app;
		return 0;
	}
#endif

#ifdef FLO_PLATFORM_MACOS
	int main(int argc, char** argv) {
		return 0;
	}
#endif

#ifdef FLO_PLATFORM_IPHONE
	int main(int argc, char** argv) {
		return 0;
	}
#endif

#ifdef FLO_PLATFORM_IPHONE_SIMULATOR
	int main(int argc, char** argv) {
		return 0;
	}
#endif

#ifdef FLO_PLATFORM_ANDROID
	int main(int argc, char** argv) {
		return 0;
	}
#endif

#ifdef FLO_PLATFORM_LINUX
	int main(int argc, char** argv) {
		return 0;
	}
#endif