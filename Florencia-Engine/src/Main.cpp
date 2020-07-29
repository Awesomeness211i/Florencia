#include "Platform.h"

#ifdef FLO_PLATFORM_WINDOWS
	#include <Windows.h>
	int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
		return 0;
	}
#endif

#ifdef FLO_PLATFORM_MACOS
	int main() {

	}
#endif

#ifdef FLO_PLATFORM_IPHONE
	int main() {

	}
#endif

#ifdef FLO_PLATFORM_IPHONE_SIMULATOR
	int main() {

	}
#endif

#ifdef FLO_PLATFORM_ANDROID
	int main() {

	}
#endif

#ifdef FLO_PLATFORM_LINUX
	int main() {

	}
#endif