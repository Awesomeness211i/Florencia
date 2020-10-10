#pragma once

#define FLO_CREATE_APP(appname) Application* CreateApplication() { return new appname(); }

#include <Core/EntryPoint.h>
namespace Florencia {
	class OrthographicCamera;
	class PerspectiveCamera;
	class Application;
	struct RenderData;
	class Renderer;
	class Console;
	class Camera;
	class Window;
	class Event;
}