#pragma once

#define FLO_CREATE_APP(appname) Application* CreateApplication() { return new appname(); }

#include <Core/EntryPoint.h>
namespace Florencia {
	class Application;
	class Renderer;
	class Console;
	class Window;
	class Event;
}